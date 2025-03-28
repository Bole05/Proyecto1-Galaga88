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

// Implement other methods similarly...