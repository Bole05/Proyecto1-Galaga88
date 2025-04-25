// Bullet.cpp
#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet()
    : active(false)
    , bulletTexture{}           
{
    rect = { 0,0,10,20 };     
}

void Bullet::Init() {
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
    if (!active) return;

    if (bulletTexture.id != 0) { 
        DrawTexture(bulletTexture, (int)rect.x, (int)rect.y, WHITE);
    }
    else {                  
        DrawRectangleRec(rect, YELLOW);
    }
}
