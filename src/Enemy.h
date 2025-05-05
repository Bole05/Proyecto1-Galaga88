// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
enum class EnemyState { ENTRY, FORMATION, DIVE, CIRCLE };
class Enemy : public Entity {
public:
    Enemy();
    void Init() override;
    void Update() override;
    void Draw() override;

    bool IsActive() const { return active; }
    void Deactivate() { active = false; }
    void Reset();         // Reposiciona y lo reactiva

   /* int GetDirection() const { return direction; }*/
    EnemyState GetState() const {
        return state;
    }
    void StartDive();
    void StartCircle();

    float GetBaseX() const { return formationPos.x; }
    void  ApplyGroupOffset(float dx) { rect.x = formationPos.x + dx; }
    void  SetGroupOffset(float dx) { groupOffset = dx; }
private:
    bool active;
    EnemyState state;
    int  direction;  // +1 o -1 para movimiento horizontal
    float angle;      
    float speed;
    Vector2 formationPos;


    Vector2 circleCenter{};
    float   circleRadius = 60.0f;
    float   circleAng = 0.0f; 
    float   circleSpeed = 2.5f;

    float patrolSpeed = 80.0f;
    float groupOffset = 0.0f;
};

#endif
