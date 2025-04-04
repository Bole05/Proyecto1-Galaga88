// Boss.h
#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"

class Boss : public Entity {
public:
    Boss();
    void Init()   override;
    void Update() override;
    void Draw()   override;

    int  GetLife() const { return life; }
    void TakeDamage(int amount) { life -= amount; }
    bool IsActive() const { return active; }
    void Activate(bool a) { active = a; }
    void SetTexture(Texture2D tex) { texture = tex; }
private:
    int  life;
    bool active;
    float speedX;
    Texture2D texture;
};

#endif
