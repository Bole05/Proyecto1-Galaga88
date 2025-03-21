#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include <vector>

class Game;

class Scene {
protected:
    Game* game;
    std::vector<Entity*> entities;
    
public:
    Scene(Game* gameRef);
    virtual ~Scene();
    
    virtual void Init() = 0;
    virtual void Update();
    virtual void Draw();
    virtual GameState CheckStateTransition() const; // Returns the current game state or a new one if transition is needed
    
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void ClearEntities();
};

#endif // SCENE_H