#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet();
    void Update() override;
    void Draw() override;
};

#endif
