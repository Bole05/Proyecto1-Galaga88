// Player.cpp
#include "Player.h"
#include "Globals.h"
#include "raylib.h"

Player::Player()
    : lives(PLAYER_LIFE)
    , spriteSheet{} 
{
  
}

void Player::Init() {
    lives = PLAYER_LIFE;
   
        // Ejemplo: 
        // Cargar la imagen (puede que lo hagas en Game y luego setees en Player)
        Image sheet = LoadImage("Arcade - Galaga 88 - Fighter.png");
        // Podrías redimensionar si quieres que cada frame sea un tamaño exacto
        // ImageResize(&sheet, algo, algo);
        spriteSheet = LoadTextureFromImage(sheet);
        UnloadImage(sheet);

        // Ajusta tu rect para la posición
        rect = { SCREEN_WIDTH / 2.0f - 16, SCREEN_HEIGHT - 32, 32, 32 };

        // Suponiendo que la hoja tiene 8 frames en horizontal y 2 filas (16 frames total)
        framesPerRow = 8;
        totalRows = 2;
        frameWidth = spriteSheet.width / framesPerRow;  // p. ej. 32
        frameHeight = spriteSheet.height / totalRows;     // p. ej. 32

        currentFrame = 0;
        frameTime = 0.1f;  // cambiar de frame cada 0.1 seg
        timer = 0.0f;

        // Estado inicial
        state = PlayerState::IDLE;
    


}

void Player::Update() {
    // (Si usas GetFrameTime())
    float delta = GetFrameTime();

    // 1) Revisar input -> estado
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
        state = PlayerState::MOVE;
    }
    else {
        state = PlayerState::IDLE;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        state = PlayerState::SHOOT;
    }

    // 2) Movimiento
    if (IsKeyDown(KEY_LEFT) && rect.x > 0) {
        rect.x -= PLAYER_SPEED;
    }
    if (IsKeyDown(KEY_RIGHT) && rect.x < SCREEN_WIDTH - rect.width) {
        rect.x += PLAYER_SPEED;
    }

    // 3) Animación
    // Digamos que tenemos un método: AnimationSegment seg = GetSegmentForState(state);
    // que devuelva la fila y startFrame/endFrame
    AnimationSegment seg = GetSegmentForState(state);

    // Avanzar el temporizador
    timer += delta;
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame++;
        if (currentFrame > seg.endFrame) {
            currentFrame = seg.startFrame; // volver al inicio
        }
    }
}
AnimationSegment Player::GetSegmentForState(PlayerState st) {
    switch (st) {
    case PlayerState::IDLE:
        return { 0, 0, 3 };   // Ejemplo fila 0, frames 0-3
    case PlayerState::MOVE:
        return { 0, 4, 7 };   // fila 0, frames 4-7
    case PlayerState::SHOOT:
        return { 1, 0, 3 };   // fila 1, frames 0-3
    case PlayerState::HURT:
        return { 1, 4, 7 };   // fila 1, frames 4-7
    default:
        return { 0, 0, 0 };
    }
}
void Player::Draw() {
    // 1) Consulta la segmentación
    AnimationSegment seg = GetSegmentForState(state);

    // 2) Calcula la fila y columna dentro de la hoja
    // Por ejemplo, la fila = seg.row
    // El offset en la fila = (currentFrame - seg.startFrame)
    int frameIndexInRow = currentFrame - seg.startFrame;
    int sourceX = frameIndexInRow * frameWidth;
    int sourceY = seg.row * frameHeight;

    // Origen
    Rectangle sourceRec{
        (float)sourceX,
        (float)sourceY,
        (float)frameWidth,
        (float)frameHeight
    };

    // Destino
    Rectangle destRec{
        rect.x, rect.y, rect.width, rect.height
    };

    DrawTexturePro(spriteSheet, sourceRec, destRec,
        Vector2{ 0.0f, 0.0f }, // origen
        0.0f,
        WHITE);
}

