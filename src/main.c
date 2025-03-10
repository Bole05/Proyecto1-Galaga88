#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <resource_dir.h>
#define SCREEN_WIDTH 610
#define SCREEN_HEIGHT 1004
#define PLAYER_SPEED 5
#define BULLET_SPEED 10
#define MAX_BULLETS 10
#define MAX_ENEMIES 20//maximo enemigos que pueden estar en una vez
#define ENEMY_BULLET_SPEED 8
#define MAX_ENEMY_BULLETS 20// 
#define PLAYER_LIFE 3
#define BOSS_LIFE 10
#define BOSS_BULLET_SPEED 12
#define MAX_Boss_BULLETS 20//

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

typedef struct {
    Rectangle rect;
    bool active;
} BossBullets;

typedef enum { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN } GameState;

void InitGame();
void UpdateGame();
void DrawGame();

GameState gameState = MENU;
Rectangle player;
Rectangle menu;
Rectangle boss;
Bullet bullets[MAX_BULLETS];
Enemy enemies[MAX_ENEMIES];
EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
BossBullets bossBullets[MAX_Boss_BULLETS];

bool bossActive = false;
int playerLife = PLAYER_LIFE;
int bossLife = BOSS_LIFE;
int score = 0;
Texture2D playerTexture;
Texture2D enemiesTexture;
Texture2D MenuTexture;
void InitEnemies();
void UpdateEnemies();
void EnemyAttack();
void BossAttack();
void UpdateBoss();

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SearchAndSetResourceDir("resources");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    Image fondo = LoadImage("fonda galaga fabricas.png");
    ImageResize(&fondo, fondo.width * 2.5, fondo.height * 2);
    Texture Menu = LoadTextureFromImage(fondo);
    InitGame();
    SetTargetFPS(60);



    while (!WindowShouldClose()) {
        UpdateGame();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Menu, 0, 0, WHITE);

        DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void InitGame() {
    gameState = MENU; 
    player = (Rectangle){ SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 50, 40, 40 };
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
  
    

    InitEnemies();
    boss = (Rectangle){ SCREEN_WIDTH / 2 - 50, 50, 100, 100 };
    bossActive = false;
    Image Menuimagen = LoadImage("menu inicial.jpg");
    ImageResize(&Menuimagen, SCREEN_WIDTH, SCREEN_HEIGHT);
    MenuTexture = LoadTextureFromImage(Menuimagen);
    UnloadImage(Menuimagen);

    Image playerImagen = LoadImage("player-removebg-preview.png");
    ImageResize(&playerImagen, 40, 40);
    playerTexture = LoadTextureFromImage(playerImagen);
    UnloadImage(playerImagen);

    Image enemiesImagen = LoadImage("fff.png");
    ImageResize(&enemiesImagen, 40, 40);
    enemiesTexture = LoadTextureFromImage(enemiesImagen);
    UnloadImage(enemiesImagen);
    for (int i = 0; i < MAX_Boss_BULLETS; i++) {
        bossBullets[i].active = false;
    }
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
    if (gameState == MENU) {
        if (IsKeyPressed(KEY_ENTER)){
            gameState = LEVEL1;
        }
    }
    else if (gameState == LEVEL1 || gameState == LEVEL2 || gameState == BOSS) {
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
            BossAttack();
        }
    }
}



    void UpdateEnemies() {
        bool allEnemiesDefeated = true; // Variable para verificar si todos los enemigos est�n derrotados

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                allEnemiesDefeated = false; // Si hay al menos un enemigo activo, no todos est�n derrotados

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

        // Si todos los enemigos est�n derrotados, cambiar al estado BOSS
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
void BossAttack() {
        for (int i = 0; i < MAX_Boss_BULLETS; i++) {
            if (!bossBullets[i].active) {
                // Disparar 3 balas en diferentes direcciones
                bossBullets[i].rect = (Rectangle){
                    boss.x + boss.width / 2 - 5,
                    boss.y + boss.height,
                    10, 20
                };
                bossBullets[i].active = true;

                // Segunda bala (disparar hacia la izquierda)
                if (i + 1 < MAX_Boss_BULLETS) {
                    bossBullets[i + 1].rect = (Rectangle){
                        boss.x + boss.width / 2 - 5,
                        boss.y + boss.height,
                        10, 20
                    };
                    bossBullets[i + 1].active = true;
                }

                // Tercera bala (disparar hacia la derecha)
                if (i + 2 < MAX_Boss_BULLETS) {
                    bossBullets[i + 2].rect = (Rectangle){
                        boss.x + boss.width / 2 - 5,
                        boss.y + boss.height,
                        10, 20
                    };
                    bossBullets[i + 2].active = true;
                }
                break; // Salir del bucle después de generar las balas
            }
        }

        // Mover las balas
        for (int i = 0; i < MAX_Boss_BULLETS; i++) {
            if (bossBullets[i].active) {
                bossBullets[i].rect.y += BOSS_BULLET_SPEED; // Mover hacia abajo
                if (bossBullets[i].rect.y > SCREEN_HEIGHT) {
                    bossBullets[i].active = false;
                }

                if (CheckCollisionRecs(bossBullets[i].rect, player)) {
                    playerLife--;
                    bossBullets[i].active = false;
                    if (playerLife <= 0) {
                        gameState = GAMEOVER;
                    }
                }
            }
        }
    }

void DrawGame() {
    if (gameState == MENU) {
        DrawTexture(MenuTexture, 0, 0, WHITE);
        // Dibujar el menú de inicio
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        
        DrawText("Presiona ENTER para comenzar", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
    }
    else {
        DrawTexture(playerTexture, player.x, player.y, WHITE);
        /*DrawRectangleRec(player, BLUE);*/
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) DrawRectangleRec(bullets[i].rect, YELLOW);
        }
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) DrawTexture(enemiesTexture, enemies[i].rect.x, enemies[i].rect.y, WHITE); ;
            /*if (enemies[i].active) DrawRectangleRec(enemies[i].rect, RED);*/
        }
        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
            if (enemyBullets[i].active) DrawRectangleRec(enemyBullets[i].rect, ORANGE);
        }
        for (int i = 0; i < MAX_Boss_BULLETS; i++) {
            if (bossBullets[i].active) {
                DrawRectangleRec(bossBullets[i].rect, PURPLE); // Dibujar las balas del boss
            }
        }

        // Dibujar el Boss solo si est� activo
        if (bossActive) {
            DrawRectangleRec(boss, DARKPURPLE);
            DrawText(TextFormat("Boss HP: %d", bossLife), SCREEN_WIDTH / 2 - 50, 10, 20, RED);
        }
        if (playerLife == 0) {
            DrawText("Game over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        }

        DrawText(TextFormat("Lives: %d", playerLife), 10, 10, 20, WHITE);
        DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH - 120, 10, 20, WHITE);
    }
}