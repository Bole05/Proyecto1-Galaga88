#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "RenderComponent.h"

class Entity {
protected:
    Vector2 position;
    Vector2 size;
    bool active;
    RenderComponent* renderer;
    
public:
    Entity(float x, float y, float width, float height);
    virtual ~Entity();
    
    virtual void Update() = 0;
    virtual void Draw();
    
    bool IsActive() const { return active; }
    void SetActive(bool isActive) { active = isActive; }
    
    Rectangle GetRect() const;
    bool CheckCollision(const Entity& other) const;
    
    // Getters and setters
    Vector2 GetPosition() const { return position; }
    void SetPosition(Vector2 newPos) { position = newPos; }
    
    Vector2 GetSize() const { return size; }
    void SetSize(Vector2 newSize) { size = newSize; }
    
    void SetRenderer(RenderComponent* newRenderer);
};

#endif // ENTITY_H