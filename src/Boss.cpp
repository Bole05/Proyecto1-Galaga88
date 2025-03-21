#include "Boss.h"

Boss::Boss(float x, float y, float width, float height, int initialHealth) :
    rect({ x, y, width, height }),
    health(initialHealth),
    direction(1) 
{}

void Boss::Update(int speed, int screenWidth) {
    rect.x += speed * direction;

    // Reverse direction upon hitting edges
    if (rect.x <= 0) {
        direction = 1;
    }
    else if (rect.x + rect.width >= screenWidth) {
        direction = -1;
    }
}
void Boss::Draw() const {
    DrawRectangleRec(rect, DARKPURPLE);
}

void Boss::TakeDamage() {
    health--;
}