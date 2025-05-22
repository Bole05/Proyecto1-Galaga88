// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "raylib.h"

class Bullet : public Entity
{
public:
    Bullet();

    /* --- disparo del jugador (sube recto) ------------------ */
    void Activate(const Vector2& pos);

    /* --- disparo con dirección libre (enemigos / boss) ----- */
    void Activate(const Vector2& pos, const Vector2& vel);
    void Init()   override;
    void Update() override;
    void Draw()   override;

    bool IsActive() const { return active; }
    void Deactivate() { active = false; }

    void SetTexture(Texture2D tex) { bulletTexture = tex; }

private:
    bool    active = false;
    Vector2 velocity{};
    Texture2D bulletTexture{};
};

#endif // BULLET_H