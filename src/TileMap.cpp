#include "TileMap.h"
#include "raylib.h"
#include <resource_dir.h>
void TileMap::LoadMap() {
    Image fondo = LoadImage("fonda galaga fabricas.png");
    ImageResize(&fondo, fondo.width * 2.5, fondo.height * 2);
    Texture Menu = LoadTextureFromImage(fondo);
}

void TileMap::DrawMap() {
    // Dibujar tiles en pantalla.
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGRAY);
}
