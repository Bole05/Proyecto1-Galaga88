// Boss.h
#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"

class Boss : public Entity {
public:
    Boss();
    void Init()   override;
    void Update() override;
    void Draw()   override;

    int  GetLife() const { return life; }
    void TakeDamage(int amount) { life -= amount; }
    bool IsActive() const { return active; }
    void Activate(bool a) { active = a; }
    void SetTexture(Texture2D tex);
private:
    int  life;
    bool active;
    float speedX;
    
    Texture2D spriteSheet; // La hoja con varios fotogramas
    int cols;              // Cuántas columnas
    int rows;              // Cuántas filas
    int totalFrames;       // cols * rows
    int currentFrame;      // fotograma actual (0..totalFrames-1)
    float frameTime;       // tiempo (segundos) entre fotogramas
    float timer;           // acumulador para cambiar de frame

    int frameWidth;        // ancho de cada fotograma
    int frameHeight;
};

#endif
