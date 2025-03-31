// Entity.h
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

    Rectangle GetRect() const { return rect; }
    void      SetRect(const Rectangle& r) { rect = r; }

protected:
    Rectangle rect{ 0, 0, 0, 0 };
};

#endif
