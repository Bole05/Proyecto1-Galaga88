#include "Enemy.h"

Enemy::Enemy() : 
    rect({0, 0, 40, 40}),
    direction(1),
    active(false)
{
}

Enemy::Enemy(float x, float y, float width, float height, int initialDirection) : 
    rect({x, y, width, height}),
    direction(initialDirection),
    active(true)
{
}

void Enemy::Update(int speed, int screenWidth) {
    if (!active) return;
    
    rect.x += direction * speed;
    
    if (rect.x < 0 || rect.x > screenWidth - rect.width) {
        direction *= -1;
    }
}

void Enemy::Draw() const {
    if (active) {
        DrawRectangleRec(rect, RED);
    }
}

void Enemy::Deactivate() {
    active = false;
}