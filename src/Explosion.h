#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "raylib.h"

class Explosion
{
public:
    // cols = fotogramas por fila – scale = 1.0f (100 %) por defecto
    void Start(Vector2 pos, Texture2D sheet, int cols,
        float frameTime = 0.08f, float scale = 1.0f)
    {
        texture = sheet;
        columns = cols;
        frameW = texture.width / columns;
        frameH = texture.height;
        position = pos;
        this->scale = scale;
        this->frameTime = frameTime;
        current = 0;
        timer = 0.0f;
        active = true;
    }

    void Update()
    {
        if (!active) return;
        timer += GetFrameTime();
        if (timer >= frameTime)
        {
            timer -= frameTime;
            if (++current >= columns) active = false;
        }
    }

    void Draw() const
    {
        if (!active) return;

        Rectangle src{ (float)(current * frameW), 0,
                       (float)frameW, (float)frameH };

        float w = frameW * scale;
        float h = frameH * scale;

        Rectangle dst{ position.x - w / 2.0f,
                       position.y - h / 2.0f,
                       w, h };

        DrawTexturePro(texture, src, dst, { 0,0 }, 0.0f, WHITE);
    }

    bool IsActive() const { return active; }

private:
    Texture2D texture{};
    Vector2   position{};
    int       columns = 1, frameW = 0, frameH = 0, current = 0;
    float     timer = 0.0f, frameTime = 0.1f, scale = 1.0f;
    bool      active = false;
};

#endif
