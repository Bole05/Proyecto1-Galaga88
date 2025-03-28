#ifndef GLOBALS_H
#define GLOBALS_H

// Screen size
#define SCREEN_WIDTH 610
#define SCREEN_HEIGHT 1004

// Player
#define PLAYER_SPEED 5
#define PLAYER_LIFE 3

// Player bullets
#define BULLET_SPEED 10
#define MAX_BULLETS 10

// Enemies
#define MAX_ENEMIES 20
#define ENEMY_BULLET_SPEED 8
#define MAX_ENEMY_BULLETS 20

// Boss
#define BOSS_LIFE 10
#define BOSS_BULLET_SPEED 12
#define MAX_BOSS_BULLETS 20

enum GameState { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN };

#endif // GLOBALS_H