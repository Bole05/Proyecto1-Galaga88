// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet();
    void Init()   override;
    void Update() override;
    void Draw()   override;

    bool IsActive() const { return active; }
    void Activate(const Vector2& pos);
    void Deactivate() { active = false; }

private:
    bool active;
};

#endif
