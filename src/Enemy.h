#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    void Update() override;
    void Draw() override;
};

#endif
