#ifndef GLOBALS_H
#define GLOBALS_H

// Tamaño de pantalla
#define SCREEN_WIDTH 610
#define SCREEN_HEIGHT 1004

// Parámetros de jugador
#define PLAYER_SPEED 5
#define PLAYER_LIFE  3

// Balas
#define BULLET_SPEED 700
#define MAX_BULLETS  10

// Enemigos
#define MAX_ENEMIES       20
#define ENEMY_BULLET_SPEED 400
#define MAX_ENEMY_BULLETS 10

// Boss
#define BOSS_LIFE        10
#define BOSS_BULLET_SPEED 500
#define MAX_BOSS_BULLETS  20

// Estados del juego
enum GameState { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN };

#endif // GLOBALS_H
