#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Globals.h"

class Player : public Entity {
public:
    Player();
    void Init() override;
    void Update() override;
    void Draw() override;

    int GetLives() const { return lives; }
    void TakeDamage() { lives--; }

private:
    int lives;
    Texture2D texture;
};

#endif