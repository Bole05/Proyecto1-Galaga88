#include "RenderComponent.h"

RenderComponent::RenderComponent(Texture2D tex, Rectangle source, Color color) {
    texture = tex;
    tint = color;
    
    if (source.width == 0 || source.height == 0) {
        sourceRect = (Rectangle){0, 0, (float)texture.width, (float)texture.height};
    } else {
        sourceRect = source;
    }
}

RenderComponent::~RenderComponent() {
    // Don't unload the texture here as it's managed by ResourceManager
}

void RenderComponent::Draw(Vector2 position, Vector2 size) {
    Rectangle destRect = {position.x, position.y, size.x, size.y};
    DrawTexturePro(texture, sourceRect, destRect, (Vector2){0, 0}, 0.0f, tint);
}