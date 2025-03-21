#include "Bullet.h"

Bullet::Bullet() : 
    rect({0, 0, 10, 20}),
    speed(0),
    active(false)
{
}

void Bullet::Activate(float x, float y, float bulletSpeed) {
    rect.x = x;
    rect.y = y;
    speed = bulletSpeed;
    active = true;
}

void Bullet::Deactivate() {
    active = false;
}

void Bullet::Update() {
    rect.y += speed;
    
    // Deactivate if out of screen bounds
    if ((speed < 0 && rect.y < 0) || (speed > 0 && rect.y > GetScreenHeight())) {
        active = false;
    }
}

void Bullet::Draw(Color color) const {
    if (active) {
        DrawRectangleRec(rect, color);
    }
}