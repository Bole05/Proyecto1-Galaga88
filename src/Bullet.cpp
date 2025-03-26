#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet() {
    rect = { 0, 0, 10, 20 };
}

void Bullet::Update() {
    rect.y -= 5; // Movimiento hacia arriba
}

void Bullet::Draw() {
    DrawRectangleRec(rect, YELLOW);
}
