#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class GameplayScene : public Scene {
private:
    int level;
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> playerBullets;
    std::vector<Bullet*> enemyBullets;
    
public:
    GameplayScene(Game* gameRef, int levelNumber);
    ~GameplayScene();
    
    void Init() override;
    void Update() override;
    void Draw() override;
    GameState CheckStateTransition() const override;
    
    // Helper methods
    //void SpawnEnemies();
    //void CheckCollisions();
};

#endif // GAMEPLAY_SCENE_H