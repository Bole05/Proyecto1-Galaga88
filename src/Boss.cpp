#include "Boss.h"
#include "Game.h"

Boss::Boss(float x, float y, int initialHealth, std::vector<Bullet*>& bulletList, Texture2D bulletTex)
    : Enemy(x, y, 1, 2, bulletList, bulletTex) {
    health = initialHealth;
    size = (Vector2){ 100, 100 };
}

Boss::~Boss() {
    // Destructor
}

void Boss::Update() {
    // Move boss
    position.x += direction * speed;
    
    // Reverse direction if hitting screen edge
    if (position.x < 0 || position.x > GetScreenWidth() - size.x) {
        direction *= -1;
    }
    
    // Random chance to shoot (higher chance than regular enemies)
    if (GetRandomValue(0, 60) < 1) {
        Shoot();
    }
}

void Boss::Shoot() {
    // Create three bullets in different directions
    float centerX = position.x + size.x/2 - 5;
    float bottomY = position.y + size.y;
    
    // Middle bullet (straight down)
    Bullet* bullet1 = new Bullet(centerX, bottomY, 10, 20, 1, 12, bulletTexture);
    bullets.push_back(bullet1);
    
    // Left bullet (diagonal left)
    Bullet* bullet2 = new Bullet(centerX, bottomY, 10, 20, 1, 12, bulletTexture);
    bullet2->SetDirection(-0.5f, 0.5f);
    bullets.push_back(bullet2);
    
    // Right bullet (diagonal right)
    Bullet* bullet3 = new Bullet(centerX, bottomY, 10, 20, 1, 12, bulletTexture);
    bullet3->SetDirection(0.5f, 0.5f);
    bullets.push_back(bullet3);
}

bool Boss::TakeDamage() {
    health--;
    return health <= 0;
}