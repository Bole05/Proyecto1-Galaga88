#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"

class Boss : public Entity {
public:
    Boss();
    void Update() override;
    void Draw() override;
};

#endif
