// Player.cpp
#include "Player.h"
#include "Globals.h"
#include "raylib.h"

Player::Player()
    : lives(PLAYER_LIFE)
    , spriteSheet{}          // Inicializa la textura en blanco
    , state(PlayerState::IDLE)
    , currentFrame(0)
    , framesPerRow(0)
    , totalRows(0)
    , frameTime(0.1f)
    , timer(0.0f)
    , frameWidth(0)
    , frameHeight(0)
{
  
}

void Player::Init() {
    lives = PLAYER_LIFE;
   
    rect = { SCREEN_WIDTH / 2.0f - 16, SCREEN_HEIGHT - 32, 32, 32 };

    // Configura la animación, asumiendo que ya tienes spriteSheet.
    framesPerRow = 8;    // hipotético
    totalRows = 2;    // hipotético
    frameWidth = spriteSheet.width / framesPerRow;
    frameHeight = spriteSheet.height / totalRows;
    currentFrame = 0;
    frameTime = 0.1f;
    timer = 0.0f;
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
    case PlayerState::IDLE: {
        AnimationSegment seg = { 0, 0, 3 };  // Fila 0, frames 0 a 3
        return seg;
    }
    case PlayerState::MOVE: {
        AnimationSegment seg = { 0, 4, 7 };  // Fila 0, frames 4 a 7
        return seg;
    }
    case PlayerState::SHOOT: {
        AnimationSegment seg = { 1, 0, 3 };  // Fila 1, frames 0 a 3
        return seg;
    }
    case PlayerState::HURT: {
        AnimationSegment seg = { 1, 4, 7 };  // Fila 1, frames 4 a 7
        return seg;
    }
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

