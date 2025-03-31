// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    void Init() override;
    void Update() override;
    void Draw() override;

    bool IsActive() const { return active; }
    void Deactivate() { active = false; }
    void Reset();         // Reposiciona y lo reactiva

    int GetDirection() const { return direction; }

private:
    bool active;
    int  direction;  // +1 o -1 para movimiento horizontal
};

#endif
