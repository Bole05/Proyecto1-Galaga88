#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(float x, float y, int dir, int spd, std::vector<Bullet*>& bulletList, Texture2D bulletTex)
    : Entity(x, y, 40, 40), bullets(bulletList) {
    direction = dir;
    speed = spd;
    bulletTexture = bulletTex;
}

Enemy::~Enemy() {
    // Destructor
}

void Enemy::Update() {
    // Move enemy
    position.x += direction * speed;
    
    // Reverse direction if hitting screen edge
    if (position.x < 0 || position.x > GetScreenWidth() - size.x) {
        direction *= -1;
    }
    
    // Random chance to shoot
    if (GetRandomValue(0, 100) < 1) {
        Shoot();
    }
}

void Enemy::Shoot() {
    Bullet* bullet = new Bullet(position.x + size.x/2 - 5, position.y + size.y, 10, 20, 1, 8, bulletTexture);
    bullets.push_back(bullet);
}