#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Entity() {}

protected:
    Rectangle rect;
};

#endif
