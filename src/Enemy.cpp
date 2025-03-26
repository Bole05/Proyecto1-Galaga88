#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy() {
    rect = { rand() % (SCREEN_WIDTH - 40), rand() % 200, 40, 40 };
}

void Enemy::Update() {
    rect.y += 2;
}

void Enemy::Draw() {
    DrawRectangleRec(rect, RED);
}
