#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(float x, float y, float width, float height, int direction, int bulletSpeed, Texture2D bulletTexture)
    : Entity(x, y, width, height) {
    dirX = 0;
    dirY = direction;
    speed = bulletSpeed;
    
    // Create simple colored rectangle renderer if no texture provided
    if (bulletTexture.id == 0) {
        // Default colors based on direction (upward/downward)
        Color bulletColor = (direction < 0) ? YELLOW : ORANGE;
        renderer = new RenderComponent(bulletTexture, {0, 0, 0, 0}, bulletColor);
    } else {
        renderer = new RenderComponent(bulletTexture);
    }
}

Bullet::~Bullet() {
    // Destructor
}

void Bullet::Update() {
    // Move bullet
    position.x += dirX * speed;
    position.y += dirY * speed;
    
    // Deactivate if out of screen
    if (position.y < 0 || position.y > GetScreenHeight() ||
        position.x < 0 || position.x > GetScreenWidth()) {
        SetActive(false);
    }
}

void Bullet::SetDirection(float dx, float dy) {
    // Normalize the direction
    float length = sqrtf(dx*dx + dy*dy);
    if (length != 0) {
        dirX = dx / length;
        dirY = dy / length;
    }
}