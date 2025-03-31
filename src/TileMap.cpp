#include "TileMap.h"
#include "raylib.h"
#include <resource_dir.h>
void TileMap::LoadMap() {
    if (FileExists("fonda galaga fabricas.png")) {
        Image fondo = LoadImage("fonda galaga fabricas.png");
        ImageResize(&fondo, SCREEN_WIDTH, SCREEN_HEIGHT);  // Redimensiona al tamaño de pantalla
        Texture Menu = LoadTextureFromImage(fondo);
        UnloadImage(fondo);  // ¡Libera la imagen después de usarla!
    }
}

void TileMap::DrawMap() {
    // Dibujar tiles en pantalla.
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGRAY);
}
