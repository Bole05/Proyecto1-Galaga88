// Boss.cpp
#include "Boss.h"
#include "raylib.h"
#include"Game.h"
Boss::Boss()
    : life(BOSS_LIFE)
    , active(false)
    , speedX(2.0f)
    , texture{}     
{
    rect = { SCREEN_WIDTH / 2.0f - 50, 50, 100, 100 };
}

void Boss::Init() {
    rect = { SCREEN_WIDTH / 2.0f - 50, 50, 100, 100 };
    life = BOSS_LIFE;
    active = false;
    speedX = 2.0f;
}

void Boss::Update() {
 //   if (!active) return;
 //   rect.x += speedX;
 ///*   static int bossSpeed = 2;
 //   rect.x += bossSpeed;
 //   if (rect.x < 0 || (rect.x + rect.width) > SCREEN_WIDTH) {
 //       bossSpeed *= -1;
 //   }*/
 //   if (rect.x < 0) {
 //       rect.x = 0;
 //       speedX = -speedX; // Invertir dirección
 //   }
 //   else if (rect.x + rect.width > SCREEN_WIDTH) {
 //       rect.x = SCREEN_WIDTH - rect.width;
 //       speedX = -speedX; // Invertir dirección
 //   }
    if (!active) return;
    // movimiento horizontal de ejemplo:
    rect.x += speedX;
    if (rect.x < 0 || rect.x + rect.width > SCREEN_WIDTH) {
        speedX = -speedX; // rebota
    }
}

void Boss::Draw() {
    /*if (!active) return;
    DrawRectangleRec(rect, PURPLE);*/
    if (!active) return;

    if (texture.id > 0) {
        // Dibuja con textura
        DrawTexture(texture, (int)rect.x, (int)rect.y, WHITE);
    }
    else {
        // fallback: dibuja un rectángulo
        DrawRectangleRec(rect, PURPLE);
    }
}
