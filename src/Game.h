#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "raylib.h" 
class Game {
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

private:
    void InitEnemies();
    void UpdateEnemies();
    void CheckAllEnemiesDefeated();
    void EnemyAttack();
    void BossAttack(); 

    void LaunchOrbitRing();
    GameState gameState;

    Player               player;
    std::vector<Enemy>   enemies;
    Boss                 boss;
    std::vector<Bullet>  playerBullets;
    std::vector<Bullet>  enemyBullets;
    std::vector<Bullet>  bossBullets;

    // Texturas
    Texture2D menuTexture;
    Texture2D backgroundTexture;
    Texture2D bossBackgroundTexture; 
  
    Texture2D playerTexture;
    Texture2D enemyTexture;
    Texture2D bossTexture; 
    Texture2D PlyBulletText;

    //audios
    Sound sfxPlayerShot{};
    Sound sfxEnemyHit{};
    Sound sfxPlayerHurt{};
    
    int  score;
    bool bossActive;
  
    float backgroundOffset; // Cuánto se ha desplazado la textura
    float backgroundSpeed;  // Velocidad de desplazamiento
  

    bool  bgTransitionActive;
    float bgAlpha;
    float bgFadeSpeed;
    float bossBgOffset = 0.0f;
    float bossBgSpeed = 1.5f;
    int   bestScore = 0;

  
    float formationOffsetX;
    float formationDir;
    float formationSpeed;

};

#endif
