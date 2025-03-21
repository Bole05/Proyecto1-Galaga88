#include "Player.h"

Player::Player(float x, float y, float width, float height, int initialLives) : 
    rect({x, y, width, height}),
    lives(initialLives)
{
}

void Player::Update() {
    if (IsKeyDown(KEY_LEFT) && rect.x > 0) {
        rect.x -= SPEED;
    }
    if (IsKeyDown(KEY_RIGHT) && rect.x < GetScreenWidth() - rect.width) {
        rect.x += SPEED;
    }
}

void Player::Draw() const {
    DrawRectangleRec(rect, BLUE);
}

void Player::TakeDamage() {
    lives--;
}