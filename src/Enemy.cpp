#include "Enemy.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy() {
    Init();  // Llama a Init() en el constructor
}

void Enemy::Init() {
    rect = {
        static_cast<float>(rand() % (SCREEN_WIDTH - 40)),
        static_cast<float>(-100),  // Aparecen arriba de la pantalla
        40.0f,
        40.0f
    };
}

void Enemy::Update() {
    rect.y += 2;  // Movimiento hacia abajo

    // Reiniciar posición si sale de pantalla
    if (rect.y > SCREEN_HEIGHT) {
        rect.y = -rect.height;
        rect.x = static_cast<float>(rand() % (SCREEN_WIDTH - 40));
    }
}

void Enemy::Draw() {
    DrawRectangleRec(rect, RED);
}