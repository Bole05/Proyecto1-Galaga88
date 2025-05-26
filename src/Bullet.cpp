// Bullet.cpp
#include "Bullet.h"
#include "Globals.h"
#include "raylib.h"

Bullet::Bullet()
{
    rect = { 0, 0, 4, 12 };
}
void Bullet::Init()
{
    // la bala no necesita inicialización adicional
}

void Bullet::Activate(const Vector2& pos)
{
    Vector2 vel{ 0, -BULLET_SPEED };
    rect.x = pos.x - rect.width * 0.5f;
    rect.y = pos.y - rect.height * 0.5f;

    prevPos = { rect.x, rect.y };
    velocity = vel;
    active = true;
}

//-----------------------------------------------------
// 3.  Activar bala con velocidad libre (enemigos / boss)
//-----------------------------------------------------
void Bullet::Activate(const Vector2& pos, const Vector2& vel)
{
    rect.x = pos.x - rect.width * 0.5f;
    rect.y = pos.y - rect.height * 0.5f;

    prevPos = { rect.x, rect.y };
    velocity = vel;
    active = true;
}

/* ---------------- update ---------------------- */
void Bullet::Update()
{
    if (!active) return;

    /* guarda posición antes de mover */
    prevPos = { rect.x, rect.y };

    float dt = GetFrameTime();
    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    if (rect.y < -rect.height || rect.y > SCREEN_HEIGHT ||
        rect.x < -rect.width || rect.x > SCREEN_WIDTH)
        active = false;
}

/* ---------------- draw ------------------------ */
void Bullet::Draw()
{
    if (!active) return;

    if (bulletTexture.id)
        DrawTexture(bulletTexture, (int)rect.x, (int)rect.y, WHITE);
    else
        DrawRectangleRec(rect, YELLOW);
}