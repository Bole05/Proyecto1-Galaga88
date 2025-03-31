#include "Game.h"
#include "raylib.h"
#include "ResourceManager.h"

Game::Game() : gameState(MENU), score(0), bossActive(false) {
    playerBullets.resize(MAX_BULLETS);
    enemyBullets.resize(MAX_ENEMY_BULLETS);
    bossBullets.resize(MAX_BOSS_BULLETS);
}

void Game::Init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    SetTargetFPS(60);

    player.Init();
    boss.Init();
    InitEnemies();

    // Load textures
    menuTexture = ResourceManager::LoadTexture("menu inicial.jpg");
    backgroundTexture = ResourceManager::LoadTexture("fonda galaga fabricas.png");
}

void Game::InitEnemies() {
    enemies.clear();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy;
        Rectangle rect = enemy.GetRect();
        rect.x = (i % 10) * (SCREEN_WIDTH / 10);
        rect.y = -((i / 10) * 50);
        enemy.Init();  // O usa un método SetPosition si lo tienes
        enemies.push_back(enemy);
    }
}

void Game::UpdateEnemies() {
    for (auto& enemy : enemies) {
        enemy.Update();

        // Eliminar enemigos que salgan de pantalla
        if (enemy.GetRect().y > SCREEN_HEIGHT) {
            enemy = Enemy(); // Reemplazar con nuevo enemigo
        }
    }
}

void Game::EnemyAttack() {
    // Lógica para que los enemigos disparen
    for (auto& enemy : enemies) {
        if (GetRandomValue(0, 100) < 2) { // 2% de probabilidad por frame
            for (auto& bullet : enemyBullets) {
                if (!bullet.IsActive()) {
                    Rectangle enemyRect = enemy.GetRect();
                    bullet.Activate({ enemyRect.x + enemyRect.width / 2, enemyRect.y + enemyRect.height });
                    break;
                }
            }
        }
    }

    // Actualizar balas enemigas
    for (auto& bullet : enemyBullets) {
        bullet.Update();
    }
}

void Game::BossAttack() {
    // Lógica para que el boss dispare
    if (GetRandomValue(0, 100) < 5) { // 5% de probabilidad por frame
        for (auto& bullet : bossBullets) {
            if (!bullet.IsActive()) {
                Rectangle bossRect = boss.GetRect();
                bullet.Activate({ bossRect.x + bossRect.width / 2, bossRect.y + bossRect.height });
                break;
            }
        }
    }

    // Actualizar balas del boss
    for (auto& bullet : bossBullets) {
        bullet.Update();
    }
}

void Game::Update() {
    if (gameState == MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = LEVEL1;
        }
    }
    else {
        player.Update();

        // Player shooting
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& bullet : playerBullets) {
                if (!bullet.IsActive()) {
                    Rectangle playerRect = player.GetRect();
                    bullet.Activate({ playerRect.x + 15, playerRect.y });
                    break;
                }
            }
        }

        // Update bullets
        for (auto& bullet : playerBullets) bullet.Update();

        UpdateEnemies();
        EnemyAttack();

        if (gameState == BOSS) {
            bossActive = true;
            boss.Update();
            BossAttack();
        }

        for (auto& bullet : playerBullets) {
            if (bullet.IsActive() && CheckCollisionRecs(bullet.GetRect(), boss.GetRect())) {
                bullet.Deactivate();
                boss.TakeDamage();
                score += 50;

                if (boss.GetLife() <= 0) {
                    gameState = WIN;
                }
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (gameState == MENU) {
        DrawTexture(menuTexture, 0, 0, WHITE);
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Presiona ENTER para comenzar", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
    }
    else {
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        player.Draw();

        for (auto& bullet : playerBullets) bullet.Draw();
        for (auto& enemy : enemies) enemy.Draw();
        for (auto& bullet : enemyBullets) bullet.Draw();

        if (bossActive) {
            boss.Draw();
            DrawText(TextFormat("Boss HP: %d", boss.GetLife()), SCREEN_WIDTH / 2 - 50, 10, 20, RED);
        }

        DrawText(TextFormat("Lives: %d", player.GetLives()), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH - 120, 10, 20, WHITE);
    }

    EndDrawing();
}