# Raylib-Quickstart
A simple cross platform template for setting up a project with the bleeding edge raylib code.
Works with C or C++.

## Supported Platforms
Quickstart supports the main 3 desktop platforms:
* Windows
* Linux
* MacOS

# Naming projects
Do not name your game project 'raylib', it will conflict with the raylib library.

# VSCode Users (all platforms)
*Note* You must have a compiler toolchain installed in addition to vscode.

* Download the quickstart
* Rename the folder to your game name
* Open the folder in VSCode
* Run the build task ( CTRL+SHIFT+B or F5 )
* You are good to go

# Windows Users
There are two compiler toolchains available for windows, MinGW-W64 (a free compiler using GCC), and Microsoft Visual Studio
## Using MinGW-W64
* Double click the `build-MinGW-W64.bat` file
* CD into the folder in your terminal
* run `make`
* You are good to go

### Note on MinGW-64 versions
Make sure you have a modern version of MinGW-W64 (not mingw).
The best place to get it is from the W64devkit from
https://github.com/skeeto/w64devkit/releases
or the version installed with the raylib installer
#### If you have installed raylib from the installer
Make sure you have added the path

`C:\raylib\w64devkit\bin`

To your path environment variable so that the compiler that came with raylib can be found.

DO NOT INSTALL ANOTHER MinGW-W64 from another source such as msys2, you don't need it.

## Microsoft Visual Studio
* Run `build-VisualStudio2022.bat`
* double click the `.sln` file that is generated
* develop your game
* you are good to go

# Linux Users
* CD into the build folder
* run `./premake5 gmake2`
* CD back to the root
* run `make`
* you are good to go

# MacOS Users
* CD into the build folder
* run `./premake5.osx gmake2`
* CD back to the root
* run `make`
* you are good to go

# Output files
The built code will be in the bin dir

# Working directories and the resources folder
The example uses a utility function from `path_utils.h` that will find the resources dir and set it as the current working directory. This is very useful when starting out. If you wish to manage your own working directory you can simply remove the call to the function and the header.

# Changing to C++
Simply rename `src/main.c` to `src/main.cpp` and re-run the steps above and do a clean build.

# Using your own code
Simply remove `src/main.c` and replace it with your code, and re-run the steps above and do a clean build.

# Building for other OpenGL targets
If you need to build for a different OpenGL version than the default (OpenGL 3.3) you can specify an OpenGL version in your premake command line. Just modify the bat file or add the following to your command line

## For OpenGL 1.1
`--graphics=opengl11`

## For OpenGL 2.1
`--graphics=opengl21`

## For OpenGL 4.3
`--graphics=opengl43`

## For OpenGLES 2.0
`--graphics=opengles2`

## For OpenGLES 3.0
`--graphics=opengles3`

# License
Copyright (c) 2020-2025 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.

#readme.md, es el sitio para describir nuestro juego, por ejemplo en qué sistema de movil,ordenador etc disponible, qué vamos hacer, de qué sobre el juego etc, es a dir es un sitio para escribir información sobre nuetro juego.


在Game Loop这个pdf中， 它告诉我们，所以的电子游戏都是通过gameloop循环来实现的，因为电子游戏不像传统应用需要用户给出指令才会执行下一步，电子游戏即使你不给出任何指令，游戏后台还会不断去刷新和计算画面。
所以我们需要不同的代码告诉电脑，我们初始情况，用户输入了什么，这个指令会造成什么影响，然后渲染，就是在屏幕上画出来，运行出来，最后就是清理。

这些不同的情况我们所使用的代码是
Setup()-->初始化游戏
Input()-->用户输入的指令
Update()-->更具用户的指令更新数据
Render()-->把这些指令展示出来
Cleanup()-->清理


#include <raylib.h>
#include <vector>
#include <resource_dir.h>	// utility header for SearchAndSetResourceDir
using namespace std;
int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");//crear el tamaño del juego, es d dir de que grande es el juego

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("Player principal.png");
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
int main(){
	InitWindow(800,600,"Galaga 88 Origen Vertion" );
	SetTargetFPS(60);
while(!WindowShouldClose()){//si el jugador no se cierra el juego
	BeginDrawing();
	ClearBackground();
	EndDrawing();

}

CloseWindow();
return 0;




	bool end=false;
	while(!end){
     Setup(){

	 }
    
	
	}
}





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