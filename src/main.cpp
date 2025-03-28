#include "raylib.h"
#include "Game.h"

int main() {
    int SCREEN_WIDTH = 1000;
    int SCREEN_HEIGHT = 800;
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");

    Game game;
    game.Init();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
