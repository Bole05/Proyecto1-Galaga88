#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "raylib.h"

class RenderComponent {
protected:
    Texture2D texture;
    Rectangle sourceRect;
    Color tint;
    
public:
    RenderComponent(Texture2D tex, Rectangle source = {0, 0, 0, 0}, Color color = WHITE);
    virtual ~RenderComponent();
    
    virtual void Draw(Vector2 position, Vector2 size);
    
    void SetTexture(Texture2D tex) { texture = tex; }
    void SetSourceRect(Rectangle rect) { sourceRect = rect; }
    void SetTint(Color color) { tint = color; }
};

#endif // RENDER_COMPONENT_H