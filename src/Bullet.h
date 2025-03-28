#ifndef BULLET_H
#define BULLET_H
#include "Globals.h"

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet();
    void Update() override;
    void Draw() override;
};

#endif
