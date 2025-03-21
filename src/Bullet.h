#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
private:
    float dirX;
    float dirY;
    int speed;
    
public:
    Bullet(float x, float y, float width, float height, int direction, int bulletSpeed, Texture2D bulletTexture);
    virtual ~Bullet();
    
    void Update() override;
    void SetDirection(float dx, float dy);
};

#endif // BULLET_H