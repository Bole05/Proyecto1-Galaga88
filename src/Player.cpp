#include "Player.h"
#include "Game.h"

Player::Player(float x, float y, int initialLives, std::vector<Bullet*>& bulletList, Texture2D bulletTex)
    : Entity(x, y, 40, 40), bullets(bulletList) {
    lives = initialLives;
    score = 0;
    speed = 5;
    bulletTexture = bulletTex;
}

Player::~Player() {
    // Destructor
}

void Player::Update() {
    // Handle player movement
    if (IsKeyDown(KEY_LEFT) && position.x > 0) {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT) && position.x < GetScreenWidth() - size.x) {
        position.x += speed;
    }
    
    // Handle shooting
    if (IsKeyPressed(KEY_SPACE)) {
        Shoot();
    }
}

void Player::Shoot() {
    Bullet* bullet = new Bullet(position.x + size.x/2 - 5, position.y, 10, 20, -1, 10, bulletTexture);
    bullets.push_back(bullet);
}

bool Player::TakeDamage() {
    lives--;
    return lives <= 0;
}