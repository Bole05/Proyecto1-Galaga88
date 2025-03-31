// Game.cpp
#include "Game.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <resource_dir.h> // Para SearchAndSetResourceDir

Game::Game()
    : gameState(MENU)
    , menuTexture{}
    , backgroundTexture{}
    , playerTexture{}
    , enemyTexture{}
    , bossTexture{}
    , score(0)
    , bossActive(false)
{
    playerBullets.resize(MAX_BULLETS);
    enemyBullets.resize(MAX_ENEMY_BULLETS);
    bossBullets.resize(MAX_BOSS_BULLETS);
}

Game::~Game() {
    // Liberar texturas si quieres
    UnloadTexture(menuTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(playerTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(bossTexture);

    CloseWindow();
}

void Game::Init() {
    // Cambiamos el directorio de recursos
    SearchAndSetResourceDir("resources");

    srand((unsigned int)time(nullptr));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    SetTargetFPS(60);

    // Cargar imágenes y texturas
    {
        // Menú
        Image menuImg = LoadImage("menu_inicial.jpg");
        ImageResize(&menuImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        menuTexture = LoadTextureFromImage(menuImg);
        UnloadImage(menuImg);

        // Fondo
        Image bgImg = LoadImage("fonda_galaga_fabricas.png");
        // Podrías redimensionar si quieres
        // ImageResize(&bgImg, X, Y);
        backgroundTexture = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);

        // Player
        Image playerImg = LoadImage("player-removebg-preview.png");
        ImageResize(&playerImg, 40, 40);
        playerTexture = LoadTextureFromImage(playerImg);
        UnloadImage(playerImg);

        // Enemy
        Image enemyImg = LoadImage("fff.png");
        ImageResize(&enemyImg, 40, 40);
        enemyTexture = LoadTextureFromImage(enemyImg);
        UnloadImage(enemyImg);

        // Boss (si tienes)
        // Image bossImg = LoadImage("boss.png");
        // bossTexture = LoadTextureFromImage(bossImg);
        // UnloadImage(bossImg);
    }

    // Inicializamos nuestras entidades
    player.Init();
    boss.Init();
    InitEnemies();
}

// Crea una tanda de enemigos
void Game::InitEnemies() {
    enemies.clear();
    enemies.resize(MAX_ENEMIES);
    for (auto& e : enemies) {
        e.Init();
    }
}

void Game::Update() {
    if (WindowShouldClose()) {
        gameState = GAMEOVER;
    }

    switch (gameState) {
    case MENU:
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = LEVEL1;
            score = 0;
            player.Init();
            boss.Init();
            InitEnemies();
        }
        break;

    case LEVEL1:
    case LEVEL2:
        player.Update();

        // Player dispara
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& pb : playerBullets) {
                if (!pb.IsActive()) {
                    Rectangle pr = player.GetRect();
                    Vector2 pos{ pr.x + pr.width / 2 - 5, pr.y };
                    pb.Activate(pos);
                    break;
                }
            }
        }

        // Actualizar balas player
        for (auto& pb : playerBullets) {
            pb.Update();
        }

        // Enemigos
        UpdateEnemies();
        EnemyAttack();

        // Balas de Enemigos
        for (auto& eb : enemyBullets) {
            if (eb.IsActive()) {
                Rectangle r = eb.GetRect();
                r.y += ENEMY_BULLET_SPEED;
                eb.SetRect(r);

                if (r.y > SCREEN_HEIGHT) {
                    eb.Deactivate();
                }

                if (CheckCollisionRecs(r, player.GetRect())) {
                    eb.Deactivate();
                    player.TakeDamage();
                    if (player.GetLives() <= 0) {
                        gameState = GAMEOVER;
                    }
                }
            }
        }

        // Si matamos a todos -> Boss
        CheckAllEnemiesDefeated();

        if (gameState == BOSS) {
            bossActive = true;
            boss.Init();
            boss.Activate(true);
        }
        break;

    case BOSS: {
        // Player
        player.Update();
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& pb : playerBullets) {
                if (!pb.IsActive()) {
                    Rectangle pr = player.GetRect();
                    Vector2 pos{ pr.x + pr.width / 2 - 5, pr.y };
                    pb.Activate(pos);
                    break;
                }
            }
        }
        for (auto& pb : playerBullets) {
            pb.Update();
        }

        // Boss
        boss.Update();
        BossAttack();

        // Balas del Boss
        for (auto& bb : bossBullets) {
            if (bb.IsActive()) {
                Rectangle r = bb.GetRect();
                r.y += BOSS_BULLET_SPEED;
                bb.SetRect(r);

                if (r.y > SCREEN_HEIGHT) {
                    bb.Deactivate();
                }

                if (CheckCollisionRecs(r, player.GetRect())) {
                    bb.Deactivate();
                    player.TakeDamage();
                    if (player.GetLives() <= 0) {
                        gameState = GAMEOVER;
                    }
                }
            }
        }

        // Colisión de las balas del Player con el Boss
        for (auto& pb : playerBullets) {
            if (pb.IsActive() && boss.IsActive()) {
                if (CheckCollisionRecs(pb.GetRect(), boss.GetRect())) {
                    pb.Deactivate();
                    boss.TakeDamage(1);
                    score += 50;
                    if (boss.GetLife() <= 0) {
                        gameState = WIN;
                    }
                }
            }
        }
    } break;

    case GAMEOVER:
    case WIN:
        // Esperar ENTER para volver a MENU
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = MENU;
        }
        break;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (gameState) {
    case MENU:
        if (menuTexture.id > 0) {
            DrawTexture(menuTexture, 0, 0, WHITE);
        }
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to start", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2, 20, WHITE);
        break;

    case LEVEL1:
    case LEVEL2:
    case BOSS:
        // Fondo
        if (backgroundTexture.id > 0) {
            DrawTexture(backgroundTexture, 0, 0, WHITE);
        }

        // Jugador
        {
            // Si quisieras sobrescribir su Draw() para usar la textura que cargaste aquí:
            Rectangle pr = player.GetRect();
            DrawTexture(playerTexture, (int)pr.x, (int)pr.y, WHITE);
        }

        // Balas Player
        for (auto& pb : playerBullets) {
            pb.Draw();
        }

        // Enemigos
        if (gameState != BOSS) {
            for (auto& e : enemies) {
                if (e.IsActive()) {
                    // Dibujar usando la textura enemyTexture
                    Rectangle er = e.GetRect();
                    DrawTexture(enemyTexture, (int)er.x, (int)er.y, WHITE);
                }
            }
        }

        // Balas Enemigos
        for (auto& eb : enemyBullets) {
            if (eb.IsActive()) {
                DrawRectangleRec(eb.GetRect(), ORANGE);
            }
        }

        // Boss
        if (bossActive && boss.IsActive()) {
            boss.Draw();
            DrawText(TextFormat("Boss HP: %d", boss.GetLife()), SCREEN_WIDTH / 2 - 50, 10, 20, RED);
        }

        // Balas Boss
        for (auto& bb : bossBullets) {
            if (bb.IsActive()) {
                DrawRectangleRec(bb.GetRect(), PURPLE);
            }
        }

        // UI
        DrawText(TextFormat("Lives: %d", player.GetLives()), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH - 120, 10, 20, WHITE);

        // Si muere el player
        if (player.GetLives() <= 0) {
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        }
        break;

    case GAMEOVER:
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;

    case WIN:
        DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;
    }

    EndDrawing();
}

// -------------------------------------------------------------------
// Métodos auxiliares privados:

void Game::UpdateEnemies() {
    for (auto& e : enemies) {
        if (!e.IsActive()) continue;
        e.Update();

        // Colisión con balas del jugador
        for (auto& pb : playerBullets) {
            if (pb.IsActive()) {
                if (CheckCollisionRecs(pb.GetRect(), e.GetRect())) {
                    pb.Deactivate();
                    e.Deactivate();
                    score += 10;
                    break;
                }
            }
        }
    }
}

void Game::CheckAllEnemiesDefeated() {
    bool allDead = true;
    for (auto& e : enemies) {
        if (e.IsActive()) {
            allDead = false;
            break;
        }
    }

    if (allDead && gameState == LEVEL1) {
        gameState = BOSS;
    }
}

void Game::EnemyAttack() {
    // Pequeña probabilidad de disparo
    if (GetRandomValue(0, 100) < 3) {
        int i = GetRandomValue(0, (int)enemies.size() - 1);
        if (enemies[i].IsActive()) {
            for (auto& eb : enemyBullets) {
                if (!eb.IsActive()) {
                    Rectangle er = enemies[i].GetRect();
                    Vector2 pos{ er.x + er.width / 2 - 5, er.y + er.height };
                    eb.Activate(pos);
                    break;
                }
            }
        }
    }
}

void Game::BossAttack() {
    if (!boss.IsActive()) return;
    // 3 balas de golpe
    if (GetRandomValue(0, 100) < 5) {
        int count = 0;
        for (auto& bb : bossBullets) {
            if (!bb.IsActive()) {
                Rectangle br = boss.GetRect();
                Vector2 pos{ br.x + br.width / 2 - 5, br.y + br.height };
                bb.Activate(pos);
                count++;
                if (count >= 3) break; // 3 balas
            }
        }
    }
}
