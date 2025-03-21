#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "ResourceManager.h"
#include "Scene.h"

typedef enum { MENU, LEVEL1, LEVEL2, BOSS, GAMEOVER, WIN } GameState;

class Game {
private:
    int screenWidth;
    int screenHeight;
    GameState state;
    ResourceManager* resources;
    Scene* currentScene;
    Texture2D backgroundTexture;
    
public:
    Game(int width, int height, const char* title);
    ~Game();
    
    void Init();
    void Run();
    void Update();
    void Draw();
    void ChangeState(GameState newState);
    
    // Getters
    int GetScreenWidth() const { return screenWidth; }
    int GetScreenHeight() const { return screenHeight; }
    GameState GetState() const { return state; }
    ResourceManager* GetResourceManager() const { return resources; }
};

#endif // GAME_H