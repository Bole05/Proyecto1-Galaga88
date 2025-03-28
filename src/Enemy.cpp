#include <cstdlib>  
#include <ctime> 
#include "Enemy.h"
#include "raylib.h"
using namespace std;

Enemy::Enemy() {
    rect = { static_cast<float>(rand() % (SCREEN_WIDTH - 40)),
             static_cast<float>(rand() % 200),
             40.0f, 40.0f };
}


void Enemy::Update() {
    rect.y += 2;
 
}

void Enemy::Draw() {
    DrawRectangleRec(rect, RED);
}
