#include "raylib.h"
#include "Game.h"
#include"resource_dir.h"
int main() {
    SearchAndSetResourceDir("resources");
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    TraceLog(LOG_INFO, "Iniciando juego...");
   /* InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");*/
    TraceLog(LOG_INFO, "Directorio actual: %s", GetWorkingDirectory());
    Game game;
    game.Init();

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }
  
    CloseWindow();
    return 0;
}