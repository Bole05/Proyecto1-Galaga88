#ifndef Enemy.h
#define Enemy.h

#include "raylib.h"

class Enemy{
    private:
    Rectangle rect;
    int direction;
    bool active;

    public:
    Enemy();
    Enemy(float x, float y, float width, float height, int initialDirection);

    void Update(int speed, int screenWidth);
    void Draw() const;
    void Deactivate();
    
    bool IsActive() const { return active; }
    float GetX() const { return rect.x; }
    float GetY() const { return rect.y; }
    Rectangle GetRect() const { return rect; }
};

#endif
