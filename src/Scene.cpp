#include "Scene.h"
#include "Game.h"

Scene::Scene(Game* gameRef) {
    game = gameRef;
}

Scene::~Scene() {
    ClearEntities();
}

void Scene::Update() {
    for (auto it = entities.begin(); it != entities.end(); ) {
        Entity* entity = *it;
        if (entity->IsActive()) {
            entity->Update();
            ++it;
        } else {
            // Remove inactive entities
            delete entity;
            it = entities.erase(it);
        }
    }
}

void Scene::Draw() {
    for (auto& entity : entities) {
        if (entity->IsActive()) {
            entity->Draw();
        }
    }
}

GameState Scene::CheckStateTransition() const {
    // Default implementation returns current state (no transition)
    return game->GetState();
}

void Scene::AddEntity(Entity* entity) {
    if (entity) {
        entities.push_back(entity);
    }
}

void Scene::RemoveEntity(Entity* entity) {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (*it == entity) {
            delete entity;
            entities.erase(it);
            break;
        }
    }
}

void Scene::ClearEntities() {
    for (auto& entity : entities) {
        delete entity;
    }
    entities.clear();
}