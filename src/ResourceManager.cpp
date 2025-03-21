#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    // Constructor
}

ResourceManager::~ResourceManager() {
    // Unload all textures
    for (auto& texture : textures) {
        UnloadTexture(texture.second);
    }
    
    // Unload all sounds
    for (auto& sound : sounds) {
        UnloadSound(sound.second);
    }
}

void ResourceManager::LoadTexture(const std::string& name, const std::string& filename) {
    Texture2D texture = LoadTexture(filename.c_str());
    textures[name] = texture;
}

Texture2D ResourceManager::GetTexture(const std::string& name) const {
    return textures.at(name);
}

void ResourceManager::UpdateTexture(const std::string& name, Texture2D texture) {
    if (textures.find(name) != textures.end()) {
        UnloadTexture(textures[name]);
    }
    textures[name] = texture;
}

void ResourceManager::LoadSound(const std::string& name, const std::string& filename) {
    Sound sound = LoadSound(filename.c_str());
    sounds[name] = sound;
}

Sound ResourceManager::GetSound(const std::string& name) const {
    return sounds.at(name);
}