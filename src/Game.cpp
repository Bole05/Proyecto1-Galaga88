#include "Game.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "BossScene.h"
#include "GameOverScene.h"
#include "WinScene.h"
#include <resource_dir.h>

Game::Game(int width, int height, const char* title) {
    screenWidth = width;
    screenHeight = height;
    state = MENU;
    
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SearchAndSetResourceDir("resources");
    InitWindow(screenWidth, screenHeight, title);
    
    resources = new ResourceManager();
    currentScene = nullptr;
}

Game::~Game() {
    delete resources;
    if (currentScene) delete currentScene;
    
    CloseWindow();
}

void Game::Init() {
    // Load common resources
    resources->LoadTexture("background", "fonda galaga fabricas.png");
    resources->LoadTexture("menu", "menu inicial.jpg");
    resources->LoadTexture("player", "player-removebg-preview.png");
    resources->LoadTexture("enemy", "fff.png");
    
    // Resize textures if needed
    Image backgroundImg = LoadImageFromTexture(resources->GetTexture("background"));
    ImageResize(&backgroundImg, backgroundImg.width * 2.5, backgroundImg.height * 2);
    resources->UpdateTexture("background", LoadTextureFromImage(backgroundImg));
    UnloadImage(backgroundImg);
    
    // Initialize with menu scene
    ChangeState(MENU);
    
    SetTargetFPS(60);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}

void Game::Update() {
    if (currentScene) {
        currentScene->Update();
        
        // Check for state transitions based on scene results
        GameState newState = currentScene->CheckStateTransition();
        if (newState != state) {
            ChangeState(newState);
        }
    }
}

void Game::Draw() {
    // Draw background texture
    DrawTexture(resources->GetTexture("background"), 0, 0, WHITE);
    
    // Draw current scene
    if (currentScene) {
        currentScene->Draw();
    }
}

void Game::ChangeState(GameState newState) {
    // Clean up previous scene
    if (currentScene) {
        delete currentScene;
        currentScene = nullptr;
    }
    
    // Create the new scene
    state = newState;
    switch (state) {
        case MENU:
            currentScene = new MenuScene(this);
            break;
        case LEVEL1:
            currentScene = new GameplayScene(this, 1);
            break;
        case LEVEL2:
            currentScene = new GameplayScene(this, 2);
            break;
        case BOSS:
            currentScene = new BossScene(this);
            break;
        case GAMEOVER:
            currentScene = new GameOverScene(this);
            break;
        case WIN:
            currentScene = new WinScene(this);
            break;
    }
    
    // Initialize the new scene
    if (currentScene) {
        currentScene->Init();
    }
}