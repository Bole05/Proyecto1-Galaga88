#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5
#define BULLET_SPEED 7
#define MAX_BULLETS 10
#define MAX_ENEMIES 10
#define ENEMY_BULLET_SPEED 4
#define MAX_ENEMY_BULLETS 5
#define PLAYER_LIFE 3
#define BOSS_LIFE 10

int enemySpeed = 2;

typedef struct {
    Rectangle rect;
    bool active;
} Bullet;

typedef struct {
    Rectangle rect;
    bool active;
    int direction;
} Enemy;

typedef struct {
    Rectangle rect;
    bool active;
} EnemyBullet;

typedef enum { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN } GameState;

void InitGame();
void UpdateGame();
void DrawGame();

GameState gameState = MENU;
Rectangle player;
Bullet bullets[MAX_BULLETS];
Enemy enemies[MAX_ENEMIES];
EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
Rectangle boss;
bool bossActive = false;
int playerLife = PLAYER_LIFE;
int bossLife = BOSS_LIFE;
int score = 0;

void InitEnemies();
void UpdateEnemies();
void EnemyAttack();
void UpdateBoss();

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void InitGame() {
    player = (Rectangle){ SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 50, 40, 40 };
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
    InitEnemies();
    boss = (Rectangle){ SCREEN_WIDTH / 2 - 50, 50, 100, 100 };
    bossActive = false;
}

void InitEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].rect = (Rectangle){ rand() % (SCREEN_WIDTH - 40), rand() % 200, 40, 40 };
        enemies[i].active = true;
        enemies[i].direction = (rand() % 2) ? 1 : -1;
    }
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) enemyBullets[i].active = false;
}

void UpdateGame() {
    if (gameState == MENU && IsKeyPressed(KEY_ENTER)) gameState = LEVEL1;

    if (gameState == LEVEL1 || gameState == LEVEL2 || gameState == BOSS) {
        if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= PLAYER_SPEED;
        if (IsKeyDown(KEY_RIGHT) && player.x < SCREEN_WIDTH - player.width) player.x += PLAYER_SPEED;

        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].rect = (Rectangle){ player.x + 15, player.y, 10, 20 };
                    bullets[i].active = true;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].rect.y -= BULLET_SPEED;
                if (bullets[i].rect.y < 0) bullets[i].active = false;
            }
        }

        UpdateEnemies();
        EnemyAttack();

        // Activar el Boss si el estado es BOSS
        if (gameState == BOSS) {
            bossActive = true;
            UpdateBoss();
        }
    }
}



    void UpdateEnemies() {
        bool allEnemiesDefeated = true; // Variable para verificar si todos los enemigos están derrotados

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                allEnemiesDefeated = false; // Si hay al menos un enemigo activo, no todos están derrotados

                enemies[i].rect.x += enemies[i].direction * enemySpeed;
                if (enemies[i].rect.x < 0 || enemies[i].rect.x > SCREEN_WIDTH - enemies[i].rect.width) {
                    enemies[i].direction *= -1;
                }
                for (int j = 0; j < MAX_BULLETS; j++) {
                    if (bullets[j].active && CheckCollisionRecs(bullets[j].rect, enemies[i].rect)) {
                        enemies[i].active = false;
                        bullets[j].active = false;
                        score += 10;
                    }
                }
            }
        }

        // Si todos los enemigos están derrotados, cambiar al estado BOSS
        if (allEnemiesDefeated && gameState == LEVEL1) {
            gameState = BOSS;
            bossActive = true; // Activar el Boss
        }
    }

void EnemyAttack() {
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (!enemyBullets[i].active) {
            int shooterIndex = rand() % MAX_ENEMIES;
            if (enemies[shooterIndex].active) {
                enemyBullets[i].rect = (Rectangle){ enemies[shooterIndex].rect.x + 15, enemies[shooterIndex].rect.y, 10, 20 };
                enemyBullets[i].active = true;
            }
        }

        if (enemyBullets[i].active) {
            enemyBullets[i].rect.y += ENEMY_BULLET_SPEED;
            if (enemyBullets[i].rect.y > SCREEN_HEIGHT) enemyBullets[i].active = false;

            if (CheckCollisionRecs(enemyBullets[i].rect, player)) {
                playerLife--;
                enemyBullets[i].active = false;
                if (playerLife <= 0) gameState = GAMEOVER;
            }
        }
    }
}
void UpdateBoss() {
    boss.x += enemySpeed;
    if (boss.x < 0 || boss.x > SCREEN_WIDTH - boss.width) {
        enemySpeed *= -1;

    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active && CheckCollisionRecs(bullets[i].rect, boss)) {
            bullets[i].active = false;
            bossLife--;
            score += 50;
            if (bossLife <= 0) gameState = WIN;
        }
    }
}
void DrawGame() {
    DrawRectangleRec(player, BLUE);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) DrawRectangleRec(bullets[i].rect, YELLOW);
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) DrawRectangleRec(enemies[i].rect, RED);
    }
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (enemyBullets[i].active) DrawRectangleRec(enemyBullets[i].rect, ORANGE);
    }

    // Dibujar el Boss solo si está activo
    if (bossActive) {
        DrawRectangleRec(boss, DARKPURPLE);
        DrawText(TextFormat("Boss HP: %d", bossLife), SCREEN_WIDTH / 2 - 50, 10, 20, RED);
    }

    DrawText(TextFormat("Lives: %d", playerLife), 10, 10, 20, WHITE);
    DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH - 120, 10, 20, WHITE);
}