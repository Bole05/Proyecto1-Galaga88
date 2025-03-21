#include "GameplayScene.h"
#include "Game.h"

GameplayScene::GameplayScene(Game* gameRef, int levelNumber) : Scene(gameRef) {
    level = levelNumber;
    player = nullptr;
}

GameplayScene::~GameplayScene() {
    // Clean up bullets
    for (auto& bullet : playerBullets) {
        delete bullet;
    }
    playerBullets.clear();
    
    for (auto& bullet : enemyBullets) {
        delete bullet;
    }
    enemyBullets.clear();
    
    // Clean up enemies
    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    
    // Player is already cleaned up by the Scene destructor
}

void GameplayScene::Init() {
    // Create player
    int screenWidth = game->GetScreenWidth();
    int screenHeight = game->GetScreenHeight();
    
    Texture2D playerTexture = game->GetResourceManager()->GetTexture("player");
    Texture2D bulletTexture = {}; // Empty texture for colored bullets
    
    player = new Player(screenWidth / 2 - 20, screenHeight - 50, 3, playerBullets, bulletTexture);
    player->SetRenderer(new RenderComponent(playerTexture));
    AddEntity(player);
    
    // Create enemies
    SpawnEnemies();
}

void GameplayScene::Update() {
    // Update all entities
    Scene::Update();
    
    // Check for collisions
    CheckCollisions();
}

void GameplayScene::Draw() {
    // Draw all entities
    Scene::Draw();
    
    // Draw UI
    DrawText(TextFormat("Lives: %d", player->GetLives()), 10, 10, 20, WHITE);
    DrawText(TextFormat("Score: %d", player->GetScore()), game->GetScreenWidth() - 120, 10, 20, WHITE);
}

GameState GameplayScene::CheckStateTransition() const {
    // Check if player is dead
    if (player->GetLives() <= 0) {
        return GAMEOVER;
    }
    
    // Check if all enemies are defeated
    bool allEnemiesDefeated = true;
    for (auto& enemy : enemies) {
        if (enemy->IsActive()) {
            allEnemiesDefeated = false;
            break;
        }
    }
    
    if (allEnemiesDefeated) {
        if (level == 1) {
            return BOSS;
        } else {
            return level + 1;
        }
    }
    
    return game->GetState();
}

void GameplayScene::SpawnEnemies();