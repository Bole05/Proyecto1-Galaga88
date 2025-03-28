#include "Game.h"
#include "raylib.h"
#include "Globals.h"
Game::Game() {
    gameState = MENU;
    player = new Player();
    boss = new Boss();
}

Game::~Game() {
    delete player;
    delete boss;
}

void Game::Init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    SetTargetFPS(60);
    player->Init();
}

void Game::Update() {
    player->Update();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    player->Draw();
    EndDrawing();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    CloseWindow();
}
