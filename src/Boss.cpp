#include <cstdlib> 
#include <ctime> 
#include "Boss.h"
#include "raylib.h"

Boss::Boss() {
    Init();
    rect = { SCREEN_WIDTH / 2 - 60, 50, 120, 120 };
}
void Boss::Init() {
    rect = { SCREEN_WIDTH / 2 - 60, 50, 120, 120 }; // Posición inicial del boss
}

void Boss::Update() {
    rect.x += (std::rand() % 2 == 0) ? 2 : -2; // Movimiento horizontal aleatorio
}

void Boss::Draw() {
    DrawRectangleRec(rect, DARKBLUE);
}
