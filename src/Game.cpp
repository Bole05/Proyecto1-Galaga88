#include "Game.h"
#include "resource_dir.h"
#include <stdlib.h>

Game::Game() :
	gameState(GameState::MENU),
	player(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 50, 40, 3),
	boss(SCREEN_WIDTH / 2 - 50, 50, 100, 100, 10),
	score(0),
	enemySpeed(2)
{
	playerBullets.resize(10);
	enemyBullets.resize(5);
	enemies.resize(MAX_ENEMIES);
}
Game::~Game() {
    UnloadTexture(menuBackground);
}

void Game::Initialize() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    SearchAndSetResourceDir("resources");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");

    Image fondo = LoadImage("fondo galaga fabricas ampliada.png");
    ImageResize(&fondo, fondo.width, fondo.height);
    menuBackground = LoadTextureFromImage(fondo);
    UnloadImage(fondo);

    InitEnemies();
    SetTargetFPS(60);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();

        BeginDrawing();
        ClearBackground(BLACK);
        Draw(); 
        EndDrawing();
    }
    CloseWindow();
}

void Game::Update() {
    if (gameState == GameState::MENU && IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::LEVEL1;
    }

    if (gameState == GameState::LEVEL1 || gameState == GameState::LEVEL2 || gameState == GameState::BOSS) {
        player.Update();

   
        for (auto& bullet : playerBullets) {
            if (bullet.IsActive()) {
                bullet.Update();
            }
        }

       
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& bullet : playerBullets) {
                if (!bullet.IsActive()) {
                    bullet.Activate(player.GetX() + 15, player.GetY(), -10); 
                    break;
                }
            }
        }

        UpdateEnemies();
        EnemyAttack();
        CheckCollisions();

        if (gameState == GameState::BOSS) {
            UpdateBoss();
        }

      
        if (player.GetLives() <= 0) {
            gameState = GameState::GAMEOVER;
        }
    }
}

void Game::Draw() {
   
    if (gameState == GameState::MENU) {
        DrawTexture(menuBackground, 0, 0, WHITE);
    }
    player.Draw();
    for (const auto& bullet : playerBullets) {
        if (bullet.IsActive()) {
            bullet.Draw(YELLOW);
        }
    }

    for (const auto& bullet : enemyBullets) {
        if (bullet.IsActive()) {
            bullet.Draw(ORANGE);
        }
    }


    for (const auto& enemy : enemies) {
        if (enemy.IsActive()) {
            enemy.Draw();
        }
    }

    
    if (gameState == GameState::BOSS) {
        boss.Draw();
        DrawText(TextFormat("Boss HP: %d", boss.GetHealth()), SCREEN_WIDTH / 2 - 50, 10, 20, RED);
    }

   
    DrawText(TextFormat("Lives: %d", player.GetLives()), 10, 10, 20, WHITE);
    DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH - 120, 10, 20, WHITE);

 
    if (gameState == GameState::MENU) {
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 40, 40, YELLOW);
        DrawText("PRESS ENTER TO START", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
    }
    else if (gameState == GameState::GAMEOVER) {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 40, 40, RED);
        DrawText(TextFormat("FINAL SCORE: %d", score), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
    }
    else if (gameState == GameState::WIN) {
        DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
        DrawText(TextFormat("FINAL SCORE: %d", score), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
    }
}

void Game::InitEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = Enemy( rand() % (SCREEN_WIDTH - 40),
            rand() % 200,
            40, 40,
            (rand() % 2) ? 1 : -1
        );
    }
}

void Game::UpdateEnemies() {
    bool allEnemiesDefeated = true;

    for (auto& enemy : enemies) {
        if (enemy.IsActive()) {
            allEnemiesDefeated = false;
            enemy.Update(enemySpeed, SCREEN_WIDTH);
        }
    }

    
    if (allEnemiesDefeated && gameState == GameState::LEVEL1) {
        gameState = GameState::BOSS;
    }
}

void Game::EnemyAttack() {
    for (auto& bullet : enemyBullets) {
        if (!bullet.IsActive()) {
            int shooterIndex = rand() % MAX_ENEMIES;
            if (enemies[shooterIndex].IsActive()) {
                float enemyX = enemies[shooterIndex].GetX();
                float enemyY = enemies[shooterIndex].GetY();
                bullet.Activate(enemyX + 15, enemyY, 8); 
            }
        }

        if (bullet.IsActive()) {
            bullet.Update();

           
            if (bullet.GetY() > SCREEN_HEIGHT) {
                bullet.Deactivate();
            }
        }
    }
}

void Game::CheckCollisions() {
  
    for (auto& bullet : playerBullets) {
        if (bullet.IsActive()) {
            for (auto& enemy : enemies) {
                if (enemy.IsActive() && CheckCollisionRecs(bullet.GetRect(), enemy.GetRect())) {
                    enemy.Deactivate();
                    bullet.Deactivate();
                    score += 10;
                }
            }
        }
    }

  
    for (auto& bullet : enemyBullets) {
        if (bullet.IsActive() && CheckCollisionRecs(bullet.GetRect(), player.GetRect())) {
            player.TakeDamage();
            bullet.Deactivate();
        }
    }
}

void Game::UpdateBoss() {
    boss.Update(enemySpeed, SCREEN_WIDTH);

    
    for (auto& bullet : playerBullets) {
        if (bullet.IsActive() && CheckCollisionRecs(bullet.GetRect(), boss.GetRect())) {
            bullet.Deactivate();
            boss.TakeDamage();
            score += 50;

            if (boss.GetHealth() <= 0) {
                gameState = GameState::WIN;
            }
        }
    }
}
