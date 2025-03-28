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

    // Añade estos métodos para manejar la vida del boss
    int GetLife() const { return life; }
    void TakeDamage() { life--; }

private:
    int life;
};

#endif