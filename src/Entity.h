#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "Globals.h"

class Entity {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Entity() {}

    // Add this method to get the rectangle
    Rectangle GetRect() const { return rect; }

protected:
    Rectangle rect;
};

#endif