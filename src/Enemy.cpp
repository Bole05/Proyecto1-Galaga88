// Enemy.cpp
#include "Enemy.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy() {
    Init();
}

void Enemy::Init() {
    Reset();
}

void Enemy::Reset() {
    rect.width = 40.0f;
    rect.height = 40.0f;
    rect.x = static_cast<float>(rand() % (SCREEN_WIDTH - 40));
    rect.y = static_cast<float>(rand() % 200); // parte superior random

    active = true;
    direction = (rand() % 2) ? 1 : -1; // 1 o -1
}

void Enemy::Update() {
    if (!active) return;

    rect.x += direction * 2;  // velocidad horizontal
    if (rect.x < 0 || rect.x > SCREEN_WIDTH - rect.width) {
        direction *= -1;
    }
}

void Enemy::Draw() {
    if (!active) return;
    DrawRectangleRec(rect, RED);  // Por defecto, un rectángulo rojo
}
