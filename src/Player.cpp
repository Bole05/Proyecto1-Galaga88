#include "Player.h"
#include "raylib.h"

Player::Player() {
    lives = PLAYER_LIFE;
}

void Player::Init() {
    rect = { SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 50, 40, 40 };
}

void Player::Update() {
    if (IsKeyDown(KEY_LEFT) && rect.x > 0) rect.x -= PLAYER_SPEED;
    if (IsKeyDown(KEY_RIGHT) && rect.x < SCREEN_WIDTH - rect.width) rect.x += PLAYER_SPEED;
}

void Player::Draw() {
    DrawRectangleRec(rect, BLUE);
}
