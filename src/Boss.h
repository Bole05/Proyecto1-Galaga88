#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"
#include "Globals.h"

class Boss : public Entity {
public:
    Boss();
    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif
