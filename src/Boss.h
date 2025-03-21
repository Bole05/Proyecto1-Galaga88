#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
private:
    int health;
    
public:
    Boss(float x, float y, int initialHealth, std::vector<Bullet*>& bulletList, Texture2D bulletTex);
    virtual ~Boss();
    
    void Update() override;
    void Shoot() override;
    
    bool TakeDamage();
    
    // Getters
    int GetHealth() const { return health; }
};

#endif // BOSS_H