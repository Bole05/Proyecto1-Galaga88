// Enemy.cpp
#include "Enemy.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include<cmath>

Enemy::Enemy() {
    Init();
}

void Enemy::Reset() {
    rect.width = 40.0f;
    rect.height = 40.0f;
    rect.x = static_cast<float>(rand() % (SCREEN_WIDTH - 40));
    rect.y = static_cast<float>(rand() % 200); // parte superior random

    active = true;
    direction = (rand() % 2) ? 1 : -1; // 1 o -1
}


void Enemy::Init()
{
    
    rect.width = 55;
    rect.height = 55;
    rect.x = (float)(rand() % (SCREEN_WIDTH - 40));
    rect.y = -rect.height;

    active = true;
    state = EnemyState::ENTRY;
    direction = (rand() % 2) ? 1 : -1;  // curva izq/der
    angle = 0.0f;
    speed = 120.0f;  // píxeles/seg

    // posición fija en la formación (fila/col)
    int col = rand() % 10;
    int row = rand() % 3;
    formationPos = { 60 + col * 50.0f,  100 + row * 50.0f };
    patrolSpeed = 60.0f + (float)(rand() % 40);


}


void Enemy::StartDive()
{
    if (state == EnemyState::FORMATION) {
        state = EnemyState::DIVE;
        direction = (rect.x < SCREEN_WIDTH / 2) ? 1 : -1;
        angle = 0.0f;
    }
}
void Enemy::StartOrbit(Enemy* anchor, float radius, float phase, float speed) {
    orbitAnchor = anchor;
    state = EnemyState::CIRCLE;
    circleRadius = radius;
    circlePhase = phase;
    circleSpeed = speed;
    circleAng = 0.0f;

    if (anchor) {
        Rectangle ar = anchor->GetRect();
        circleCenter = { ar.x + ar.width / 2.0f, ar.y + ar.height / 2.0f };
    }
}
void Enemy::SetSprite(Texture2D tex, int cols, float secPerFrame)
{
    sprite = tex;
    frameCols = cols;
    frameTime = secPerFrame;

    currentFrame = 0;
    timer = 0.0f;
}

void Enemy::Update()
{
    if (!active) return;

    float dt = GetFrameTime();

    if (sprite.id != 0)
    {
        timer += dt;
        if (timer >= frameTime)
        {
            timer -= frameTime;
            currentFrame = (currentFrame + 1) % frameCols;   // 0?1?0…
        }
    }

    switch (state)
    {
    case EnemyState::ENTRY:     /* vuelo ondulado hasta llegar a su casilla */
        angle += 3.0f * dt;     // velocidad angular
        rect.y += speed * dt;
        rect.x += sinf(angle * 2) * 60 * dt * direction;

        if (rect.y >= formationPos.y) {
            rect = { formationPos.x, formationPos.y, rect.width, rect.height };
            state = EnemyState::FORMATION;
        }
        break;

    case EnemyState::FORMATION:
        rect.x = formationPos.x + groupOffset;
        rect.y = formationPos.y;
        break;

    case EnemyState::DIVE:      /* zambullida en curva senoidal */
        angle += 4.0f * dt;
        rect.y += speed * 1.2f * dt;
        rect.x += sinf(angle * 3) * 100 * dt * direction;

        if (rect.y > SCREEN_HEIGHT) {   // sale de pantalla ? regresa a formación
            rect.y = -rect.height;
            state = EnemyState::ENTRY;
            angle = 0.0f;
        }
        break;
    case EnemyState::CIRCLE:
        if (orbitAnchor && orbitAnchor->IsActive()) {
            Rectangle ar = orbitAnchor->GetRect();
            circleCenter = { ar.x + ar.width / 2.0f, ar.y + ar.height / 2.0f };
        }
        circleAng += circleSpeed * dt;
        rect.x = circleCenter.x + cosf(circleAng + circlePhase) * circleRadius - rect.width / 2.0f;
        rect.y = circleCenter.y + sinf(circleAng + circlePhase) * circleRadius - rect.height / 2.0f;

        if (circleAng >= 2 * PI) {
            rect = { formationPos.x, formationPos.y, rect.width, rect.height };
            state = EnemyState::FORMATION;
            orbitAnchor = nullptr;
        }
        break;
    }
}

void Enemy::Draw()
{
    // Intencionalmente vacío (Game.cpp ya usa Draw(playerRect))
}

void Enemy::Draw(const Rectangle& playerRect)
{
    if (!active) return;

    if (sprite.id != 0)
    {
        /* ===== 1) escala ==================================== */
        const float scale = 0.7f;          // usa el tamaño exacto

        int fw = sprite.width / frameCols;
        int fh = sprite.height;

        Rectangle src{ (float)(currentFrame * fw), 0, (float)fw, (float)fh };

        Rectangle dst{ rect.x, rect.y,
                       rect.width * scale,
                       rect.height * scale };

        /* ===== 2) ángulo fijo hacia abajo =================== */
        float angleDeg = 360.0f;           // todos apuntan al jugador

        // --- dibuja ---
        DrawTexturePro(sprite, src, dst,
            { dst.width / 2, dst.height / 2 },
            angleDeg,
            WHITE);
    }
}