#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "Globals.h"

class Sprite {
public:
    Sprite(Texture2D texture);
    void Draw(float x, float y);
private:
    Texture2D texture;
};

#endif
