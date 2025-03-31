// Bullet.cpp
#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet() {
    Init();
}

void Bullet::Init() {
    rect = { 0, 0, 10, 20 };
    active = false;
}

void Bullet::Activate(const Vector2& pos) {
    rect.x = pos.x;
    rect.y = pos.y;
    active = true;
}

void Bullet::Update() {
    if (!active) return;
    rect.y -= BULLET_SPEED;
    if (rect.y < 0) {
        active = false;
    }
}

void Bullet::Draw() {
    if (active) {
        DrawRectangleRec(rect, YELLOW);
    }
}
