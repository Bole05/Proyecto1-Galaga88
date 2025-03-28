#ifndef SCENE_H
#define SCENE_H
#include "Globals.h"

class Scene {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() {}
};

#endif
