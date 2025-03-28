#include "Boss.h"
#include "raylib.h"
#include <cstdlib> 
#include <ctime> 

Boss::Boss() : life(BOSS_LIFE) {
    Init();
}

void Boss::Init() {
    rect = { SCREEN_WIDTH / 2 - 60, 50, 120, 120 };
}

void Boss::Update() {
    rect.x += (std::rand() % 2 == 0) ? 2 : -2; // Movimiento horizontal aleatorio
}

void Boss::Draw() {
    DrawRectangleRec(rect, DARKBLUE);
}
