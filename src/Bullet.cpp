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

/* —— versión con dirección libre —— */
void Bullet::Activate(const Vector2& pos, const Vector2& vel)
{
    rect.x = pos.x - rect.width / 2;
    rect.y = pos.y - rect.height / 2;
    velocity = vel;
    active = true;
}

/* —— versión jugador vertical —— */
void Bullet::Activate(const Vector2& pos)
{
    Vector2 vel{ 0, -BULLET_SPEED * 60.0f };   // ? multiplica por FPS
    Activate(pos, vel);
}

/* ---------------- update ---------------------- */
void Bullet::Update()
{
    if (!active) return;

    float dt = GetFrameTime();
    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    if (rect.y < -rect.height || rect.y > SCREEN_HEIGHT ||
        rect.x < -rect.width || rect.x >  SCREEN_WIDTH)
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