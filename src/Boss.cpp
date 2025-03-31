#include "Boss.h"
#include "raylib.h"
#include <cstdlib> 
#include <ctime> 

Boss::Boss() : life(BOSS_LIFE) {
    rect = { SCREEN_WIDTH / 2 - 50, 50, 100, 100 };
}

void Boss::Init() {
    rect = { SCREEN_WIDTH / 2 - 50, 50, 100, 100 };
    life = BOSS_LIFE;
}

void Boss::Update() {
    rect.x += (std::rand() % 2 == 0) ? 2 : -2; // Movimiento horizontal aleatorio
}

void Boss::Draw() {
    DrawRectangleRec(rect, DARKBLUE);
}