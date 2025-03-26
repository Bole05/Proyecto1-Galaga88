#include "Sprite.h"

Sprite::Sprite(Texture2D texture) {
    this->texture = texture;
}

void Sprite::Draw(float x, float y) {
    DrawTexture(texture, x, y, WHITE);
}
