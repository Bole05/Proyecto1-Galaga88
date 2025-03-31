#ifndef ENEMY_H
#define ENEMY_H

#include "Globals.h"
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    void Init() override;  // Añade esta declaración
    void Update() override;
    void Draw() override;
};

#endif