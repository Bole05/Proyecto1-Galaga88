#include "Game.h"

int main(void) {
    Game game(610, 1004, "Galaga 88 - Raylib");
    game.Init();
    game.Run();
    return 0;
}