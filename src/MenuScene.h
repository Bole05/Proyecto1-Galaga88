#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"

class MenuScene : public Scene {
private:
    Texture2D menuTexture;
    
public:
    MenuScene(Game* gameRef);
    ~MenuScene();
    
    void Init() override;
    void Update() override;
    void Draw() override;
    GameState CheckStateTransition() const override;
};

#endif // MENU_SCENE_H