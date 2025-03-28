#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "TileMap.h"
#include "ResourceManager.h"
#include "Globals.h"

class Game {
public:
    Game();
    ~Game();
    void Init();
    void Update();
    void Draw();
    void Run();
private:
    GameState gameState;
    Player* player;
    std::vector<Enemy> enemies;
    Boss* boss;
    TileMap* tileMap;
};

#endif
