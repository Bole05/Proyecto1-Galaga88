#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Bullet.h"
#include <vector>

class Player : public Entity {
private:
    int lives;
    int score;
    int speed;
    std::vector<Bullet*>& bullets;
    Texture2D bulletTexture;
    
public:
    Player(float x, float y, int initialLives, std::vector<Bullet*>& bulletList, Texture2D bulletTex);
    virtual ~Player();
    
    void Update() override;
    void Shoot();
    bool TakeDamage();
    
    // Getters and setters
    int GetLives() const { return lives; }
    int GetScore() const { return score; }
    void AddScore(int points) { score += points; }
};

#endif // PLAYER_H