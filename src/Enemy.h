#ifndef ENEMY_H
#define ENEMY_H

#include "Globals.h"
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    void Init() override;  // A�ade esta declaraci�n
    void Update() override;
    void Draw() override;
};

#endif