// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "raylib.h"
enum class PlayerState {
    IDLE,    // quieto
    MOVE,    // movi�ndose
    SHOOT,   // disparando
    HURT     // da�ado
    
};
// Un struct para mapear
struct AnimationSegment {
    int row;         // en qu� fila est� la animaci�n
    int startFrame;  // en esa fila, de qu� frame a qu� frame
    int endFrame;
};

inline AnimationSegment idleAnim = { 0, 0, 3 }; // fila 0, frames 0..3
inline AnimationSegment moveAnim = { 0, 4, 7 }; // fila 0, frames 4..7
inline AnimationSegment shootAnim = { 1, 0, 3 }; // fila 1, frames 0..3

class Player : public Entity {
public:
    Player();
    void Init()   override;
    void Update() override;
    void Draw()   override;
    void SetTexture(Texture2D tex) { spriteSheet = tex; }
    int  GetLives() const { return lives; }
    void TakeDamage() { lives--; }

private:
    int       lives;
    //Texture2D texture; // Si usas texturas para dibujarlo
    Texture2D spriteSheet;

    // Datos de animaci�n
    PlayerState state;   // estado actual (IDLE, MOVE, SHOOT...)
    int currentFrame;    // fotograma que se est� mostrando
    int framesPerRow;    // cu�ntos fotogramas hay en la fila
    int totalRows;       // cu�ntas filas hay
    float frameTime;     // cada cu�ntos seg cambiamos de fotograma
    float timer;         // tiempo acumulado para pasar al siguiente frame

    int frameWidth;      // ancho de un fotograma
    int frameHeight;
    AnimationSegment GetSegmentForState(PlayerState st);
};

#endif
