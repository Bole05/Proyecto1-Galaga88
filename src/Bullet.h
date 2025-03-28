#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "Globals.h"

class Bullet : public Entity {
public:
    Bullet();
    void Update() override;
    void Draw() override;

    bool IsActive() const { return active; }
    void Activate(Vector2 position);
    void Deactivate() { active = false; }

private:
    bool active;
};

#endif