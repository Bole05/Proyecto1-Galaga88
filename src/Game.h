#ifndef GAME_H
#define GAME_H
#include "Globals.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "TileMap.h"
#include "ResourceManager.h"


class Game {
private:
    GameState gameState;
    Player* player;
    std::vector<Enemy> enemies;
    Boss* boss;
    TileMap* tileMap;
public:
    Game();
    ~Game();
    void Init();
    void Update();
    void Draw();
    void Run();

};

#endif
