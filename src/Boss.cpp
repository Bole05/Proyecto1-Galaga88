#include "Boss.h"

Boss::Boss(float x, float y, float width, float height, int initialHealth) : 
    rect({x, y, width, height}),
    health(initialHealth)
{
}

void Boss::Update(int speed, int screenWidth) {
    rect.x += speed;
    
    if (rect.x < 0 || rect.x > screenWidth - rect.width) {
        // This would normally change the direction, but we're relying on Game class to do it
    }
}

void Boss::Draw() const {
    DrawRectangleRec(rect, DARKPURPLE);
}

void Boss::TakeDamage() {
    health--;
}