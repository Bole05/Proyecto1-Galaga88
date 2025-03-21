#include "Entity.h"

Entity::Entity(float x, float y, float width, float height) {
    position = (Vector2){ x, y };
    size = (Vector2){ width, height };
    active = true;
    renderer = nullptr;
}

Entity::~Entity() {
    if (renderer) {
        delete renderer;
    }
}

void Entity::Draw() {
    if (active && renderer) {
        renderer->Draw(position, size);
    }
}

Rectangle Entity::GetRect() const {
    return (Rectangle) { position.x, position.y, size.x, size.y };
}

bool Entity::CheckCollision(const Entity& other) const {
    return CheckCollisionRecs(GetRect(), other.GetRect());
}

void Entity::SetRenderer(RenderComponent* newRenderer) {
    if (renderer) {
        delete renderer;
    }
    renderer = newRenderer;
}