// Boss.cpp
#include "Boss.h"
#include "raylib.h"

Boss::Boss()
    : life(BOSS_LIFE)
    , active(false)
{
    rect = { SCREEN_WIDTH / 2.0f - 50, 50, 100, 100 };
}

void Boss::Init() {
    rect = { SCREEN_WIDTH / 2.0f - 50, 50, 100, 100 };
    life = BOSS_LIFE;
    active = false;
}

void Boss::Update() {
    if (!active) return;

    static int bossSpeed = 2;
    rect.x += bossSpeed;
    if (rect.x < 0 || (rect.x + rect.width) > SCREEN_WIDTH) {
        bossSpeed *= -1;
    }
}

void Boss::Draw() {
    if (!active) return;
    DrawRectangleRec(rect, PURPLE);
}
