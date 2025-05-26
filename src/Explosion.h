#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "raylib.h"
class Explosion
{
public:
    void Start(Vector2 pos, Texture2D sheet, int cols, float frameTime = 0.08f)
    {
        texture = sheet;
        columns = cols;
        frameW = texture.width / columns;
        frameH = texture.height;
        position = pos;
        timer = 0.0f;
        current = 0;
        active = true;
        this->frameTime = frameTime;
    }
    void Update()
    {
        if (!active) return;
        timer += GetFrameTime();
        if (timer >= frameTime)
        {
            timer -= frameTime;
            current++;
            if (current >= columns) active = false;
        }
    }
    void Draw() const
    {
        if (!active) return;
        Rectangle src{ (float)(current * frameW), 0,
                       (float)frameW, (float)frameH };
        Rectangle dst{ position.x - frameW / 2.0f,
                       position.y - frameH / 2.0f,
                       (float)frameW, (float)frameH };
        DrawTexturePro(texture, src, dst, { 0,0 }, 0.0f, WHITE);
    }
    bool IsActive() const { return active; }
private:
    Texture2D texture{};
    Vector2   position{};
    int       columns = 1;
    int       frameW = 0, frameH = 0;
    int       current = 0;
    float     timer = 0.0f;
    float     frameTime = 0.1f;
    bool      active = false;
};
#endif
