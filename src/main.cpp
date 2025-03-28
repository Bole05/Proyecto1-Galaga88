#include "raylib.h"
#include "Game.h"
#include "Globals.h"
#include <cstdlib>
#include <ctime>
int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    std::srand(std::time(NULL));  // Inicializa la semilla aleatoria

   
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
