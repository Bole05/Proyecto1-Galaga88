#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include <vector>

class Game {
private:
    GameState gameState;
    Player player;
    std::vector<Enemy> enemies;
    Boss boss;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Bullet> bossBullets;

    Texture2D menuTexture;
    Texture2D backgroundTexture;

    int score;
    bool bossActive;

    void InitEnemies();
    void UpdateEnemies();
    void EnemyAttack();
    void BossAttack();
    void UpdateBoss();

public:
    Game();
    void Init();
    void Update();
    void Draw();
    void Run();
};

#endif