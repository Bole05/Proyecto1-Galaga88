// Player.cpp
#include "Player.h"
#include "Globals.h"
#include "raylib.h"

Player::Player()
    : lives(PLAYER_LIFE)
    , texture{}
{
    // Constructor vacío; podrías cargar la textura aquí si quieres.
}

void Player::Init() {
    lives = PLAYER_LIFE;
    rect = { SCREEN_WIDTH / 2.0f - 20, SCREEN_HEIGHT - 50, 40, 40 };
    // Podrías cargar la textura aquí o hacerlo en la clase Game 
    // y asignarla si la clase Player tuviera un setter.
}

void Player::Update() {
    if (IsKeyDown(KEY_LEFT) && rect.x > 0) {
        rect.x -= PLAYER_SPEED;
    }
    if (IsKeyDown(KEY_RIGHT) && rect.x < SCREEN_WIDTH - rect.width) {
        rect.x += PLAYER_SPEED;
    }
}

void Player::Draw() {
    if (texture.id > 0) {
        DrawTexture(texture, (int)rect.x, (int)rect.y, WHITE);
    }
    else {
        DrawRectangleRec(rect, BLUE);
    }
}
