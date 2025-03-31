#include "Bullet.h"
#include "raylib.h"

// A�ade la implementaci�n de Init()
void Bullet::Init() {
    // Puedes inicializar valores aqu� si es necesario
    rect = { 0, 0, 10, 20 };
    active = false;
}

Bullet::Bullet() {
    Init(); // Llama a Init() en el constructor
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