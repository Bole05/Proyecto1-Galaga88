#include "Boss.h"
#include "raylib.h"

Boss::Boss() {
    rect = { SCREEN_WIDTH / 2 - 60, 50, 120, 120 };
}

void Boss::Update() {
    rect.x += (rand() % 2 == 0) ? 2 : -2; // Movimiento horizontal aleatorio
}

void Boss::Draw() {
    DrawRectangleRec(rect, DARKBLUE);
}
