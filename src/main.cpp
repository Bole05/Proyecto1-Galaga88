// main.cpp
#include "Game.h"
#include "raylib.h"

int main() {
    Game game;
    game.Init();

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    return 0;
}
