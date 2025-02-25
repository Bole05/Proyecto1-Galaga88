#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5
#define BULLET_SPEED 7
#define ENEMY_SPEED 2
#define MAX_BULLETS 10
#define MAX_ENEMIES 10

typedef struct {
    Rectangle rect;
    bool active;
} Bullet;

typedef struct {
    Rectangle rect;
    bool active;
} Enemy;

typedef enum { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN } GameState;

void InitGame();
void UpdateGame();
void DrawGame();

GameState gameState = MENU;
Rectangle player;
Bullet bullets[MAX_BULLETS];
Enemy enemies[MAX_ENEMIES];
Rectangle boss;
bool bossActive = false;

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
    player = (Rectangle){ SCREEN_WIDTH/2 - 20, SCREEN_HEIGHT - 50, 40, 40 };
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].rect = (Rectangle){ rand() % (SCREEN_WIDTH - 40), rand() % 200, 40, 40 };
        enemies[i].active = true;
    }
    boss = (Rectangle){ SCREEN_WIDTH / 2 - 50, 50, 100, 100 };
    bossActive = false;
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
        
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                enemies[i].rect.y += ENEMY_SPEED;
                if (enemies[i].rect.y > SCREEN_HEIGHT) {
                    enemies[i].rect.y = 0;
                    enemies[i].rect.x = rand() % (SCREEN_WIDTH - 40);
                }
                for (int j = 0; j < MAX_BULLETS; j++) {
                    if (bullets[j].active && CheckCollisionRecs(bullets[j].rect, enemies[i].rect)) {
                        enemies[i].active = false;
                        bullets[j].active = false;
                    }
                }
            }
        }
        
        bool allEnemiesDefeated = true;
        for (int i = 0; i < MAX_ENEMIES; i++) if (enemies[i].active) allEnemiesDefeated = false;
        
        if (allEnemiesDefeated) {
            if (gameState == LEVEL1) gameState = LEVEL2;
            else if (gameState == LEVEL2) {
                gameState = BOSS;
                bossActive = true;
            }
        }
        
        if (bossActive) {
            boss.y += 1;
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active && CheckCollisionRecs(bullets[i].rect, boss)) {
                    bossActive = false;
                    gameState = WIN;
                }
            }
        }
    }
}

void DrawGame() {
    if (gameState == MENU) {
        DrawText("Press ENTER to Start", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 20, WHITE);
    } else if (gameState == LEVEL1 || gameState == LEVEL2 || gameState == BOSS) {
        DrawRectangleRec(player, BLUE);
        for (int i = 0; i < MAX_BULLETS; i++) if (bullets[i].active) DrawRectangleRec(bullets[i].rect, RED);
        for (int i = 0; i < MAX_ENEMIES; i++) if (enemies[i].active) DrawRectangleRec(enemies[i].rect, GREEN);
        if (bossActive) DrawRectangleRec(boss, PURPLE);
    } else if (gameState == WIN) {
        DrawText("YOU WIN!", SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2, 20, GREEN);
    }
}

