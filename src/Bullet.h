#ifndef Bullet_H
#define Bullet_H

#include "raylib.h"

class Bullet{
    private:
    Rectangle rect;
    float speed;
    bool active;

public:
    Bullet();
    
    void Activate(float x, float y, float bulletSpeed);
    void Deactivate();
    void Update();
    void Draw(Color color) const;
    
    bool IsActive() const { return active; }
    float GetY() const { return rect.y; }
    Rectangle GetRect() const { return rect; }
};

#endif