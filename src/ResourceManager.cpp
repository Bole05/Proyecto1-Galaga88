#include "ResourceManager.h"

std::unordered_map<std::string, Texture2D> ResourceManager::textures;

Texture2D ResourceManager::LoadTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        textures[filename] = LoadTexture(filename.c_str());
    }
    return textures[filename];
}

void ResourceManager::UnloadAll() {
    for (auto& texture : textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}
