#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include<vector>
#include<memory>
#include"Player.h"
<<<<<<< HEAD
#include <iostream>
using namespace std;

enum class GameState {MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN };

class Game{
    private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 1000;
    const int MAX_ENEMIES = 10;

     GameState gameState;
    Player player;
    vector<Enemy> enemies;
    vector<Bullet> playerBullets;
    vector<Bullet> enemyBullets;
    Boss boss;
    Texture menuBackground;
    int score;
    int enemySpeed;

    public:
    Game()
    ~Game()

    void Initialize();
    void Run();
    void Update();
    void Draw();
    
private:
    void InitEnemies();
    void UpdateEnemies();
    void EnemyAttack();
    void CheckCollisions();
    void UpdateBoss();

};

#endif
=======
#include""
>>>>>>> 66867cea5ad7606a8efe8525f7ec47ed92f0f18f
