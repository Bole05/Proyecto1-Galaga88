#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet() : active(false) {
    rect = { 0, 0, 10, 20 };
}

void Bullet::Activate(Vector2 position) {
    rect.x = position.x;
    rect.y = position.y;
    active = true;
}

void Bullet::Update() {
    if (active) {
        rect.y -= BULLET_SPEED;
        if (rect.y < 0) active = false;
    }
}

void Bullet::Draw() {
    if (active) {
        DrawRectangleRec(rect, YELLOW);
    }
}