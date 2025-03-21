#include "MenuScene.h"
#include "Game.h"

MenuScene::MenuScene(Game* gameRef) : Scene(gameRef) {
}

MenuScene::~MenuScene() {
}

void MenuScene::Init() {
    menuTexture = game->GetResourceManager()->GetTexture("menu");
}

void MenuScene::Update() {
    // Check for enter key to start the game
}

void MenuScene::Draw() {
    // Draw menu background
    DrawTexture(menuTexture, 0, 0, WHITE);
    
    // Draw menu text
    DrawText("GALAGA 88", game->GetScreenWidth() / 2 - 100, game->GetScreenHeight() / 2 - 50, 40, WHITE);
    DrawText("Presiona ENTER para comenzar", game->GetScreenWidth() / 2 - 150, game->GetScreenHeight() / 2, 20, WHITE);
}

GameState MenuScene::CheckStateTransition() const {
    if (IsKeyPressed(KEY_ENTER)) {
        return LEVEL1;
    }
    return MENU;
}