// Boss.cpp
#include "Boss.h"
#include "raylib.h"
#include"Game.h"
#include <cmath>
Boss::Boss()
    : active(false)
    , life(BOSS_LIFE)
    , speedX(2.0f)
    , spriteSheet{}
    , cols(4)
    , rows(4)
    , totalFrames(16)
    , currentFrame(0)
    , frameTime(0.15f)
    , timer(0.0f)
    , frameWidth(0)
    , frameHeight(0)
{
    rect = { SCREEN_WIDTH / 2.0f - 44.5f, 50, 89, 79 };
}

void Boss::Init() {
    //rect = { SCREEN_WIDTH / 2.0f - 50, 50, 100, 100 };
    //life = BOSS_LIFE;
    //active = false;
    //speedX = 2.0f;
    active = false;
    life = BOSS_LIFE;
    speedX = 2.0f;

    rect.x = SCREEN_WIDTH / 2.0f - 44.5f;
    rect.y = 50;
    rect.width = 89;
    rect.height = 79;

    // Reiniciamos animación
    currentFrame = 0;
    timer = 0.0f;
}
void Boss::SetTexture(Texture2D tex) {
    spriteSheet = tex;
    // Calculamos el tamaño de cada fotograma
    // Asumiendo 4x4, la imagen mide 357x319 aprox,
    // haz un floor/int para recortar
    frameWidth = spriteSheet.width / cols; // ~ 357/4 = ~89
    frameHeight = spriteSheet.height / rows; // ~ 319/4 = ~79
}
void Boss::Update() {

    if (!active) return;

    // Movimiento horizontal de ejemplo
    float delta = GetFrameTime();
    rect.x += speedX * delta * 60.0f;
    // Rebotar en bordes
    if (rect.x < 0) {
        rect.x = 0;
        speedX = -speedX;
    }
    else if (rect.x + rect.width > SCREEN_WIDTH) {
        rect.x = SCREEN_WIDTH - rect.width;
        speedX = -speedX;
    }

    // Animación
    timer += delta;
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame++;
        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }
    }
}

void Boss::Draw() {
    if (!active) return;

    // Si no hay spriteSheet, dibujamos un recuadro
    if (spriteSheet.id == 0) {
        DrawRectangleRec(rect, RED);
        return;
    }

    // Calculamos en qué columna/fila está el currentFrame
    int frameCol = currentFrame % cols;
    int frameRow = currentFrame / cols;

    // El rectángulo de origen (en la imagen)
    Rectangle sourceRec{
        (float)(frameCol * frameWidth),  // X
        (float)(frameRow * frameHeight), // Y
        (float)frameWidth,               // ancho por fotograma
        (float)frameHeight               // alto por fotograma
    };

    // El rectángulo destino (donde lo pintamos)
    Rectangle destRec{
        rect.x,
        rect.y,
        rect.width,
        rect.height
    };

    // Si no necesitas invertir la imagen, la dejas así.
    // Si quieres voltear la imagen horizontalmente, harías sourceRec.width *= -1, etc.

    // Dibujamos con DrawTexturePro
    DrawTexturePro(spriteSheet, sourceRec, destRec,
        { 0.0f, 0.0f },  // Origen (sin offset)
        0.0f,           // Rotación
        WHITE);
}
