#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Bullet.h"
#include <vector>

class Enemy : public Entity {
protected:
    int direction;
    int speed;
    std::vector<Bullet*>& bullets;
    Texture2D bulletTexture;
    
public:
    Enemy(float x, float y, int dir, int spd, std::vector<Bullet*>& bulletList, Texture2D bulletTex);
    virtual ~Enemy();
    
    void Update() override;
    virtual void Shoot();
    
    // Getters and setters
    int GetDirection() const { return direction; }
    void SetDirection(int dir) { direction = dir; }
};

#endif // ENEMY_H