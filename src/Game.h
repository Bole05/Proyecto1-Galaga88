#ifndef GAME_H
#define GAME_H
#define NOGDI          // evita conflicto MAX_PATH
#define NOMINMAX 
#include <vector>
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "raylib.h" 
#include "Explosion.h"     
class Game {
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

private:
    int wave = 1;

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
  
    Texture2D explBossTex{};
  std::vector<Explosion> bossExplosions;

    Texture2D playerTexture;
    Texture2D bossTexture; 
    Texture2D PlyBulletText;
//Enemigos
    static constexpr int NUM_ENEMY_TYPES = 5;
    std::vector<Texture2D> enemyTextures;
    Texture2D enemyBulletTex{};
    Texture2D bossBulletTex1{};   //  ? NUEVO
    Texture2D bossBulletTex2{};

    //audios
    Sound sfxPlayerShot{};
    Sound sfxEnemyHit{};
    Sound sfxPlayerHurt{};
    

    Music  bgmStage{};
    Music  bgmMenu{};
    Music  bgmGameOver{};
    
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

    Texture2D              explPlayerTex{};
    std::vector<Explosion> playerExplosions;

};

#endif
