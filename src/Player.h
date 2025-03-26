#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
    Player();
    void Init() override;
    void Update() override;
    void Draw() override;
private:
    int lives;
};

#endif
