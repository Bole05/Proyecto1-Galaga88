#include "ResourceManager.h"

std::unordered_map<std::string, Texture2D> ResourceManager::textures;

Texture2D ResourceManager::LoadTexture(const std::string& filename) {
    TraceLog(LOG_INFO, "Intentando cargar: %s", filename.c_str()); // <-- Añade esto

    if (textures.find(filename) == textures.end()) {
        if (FileExists(filename.c_str())) {
            textures[filename] = LoadTexture(filename.c_str());
            TraceLog(LOG_INFO, "Textura cargada: %s (%dx%d)",
                filename.c_str(),
                textures[filename].width,
                textures[filename].height); // <-- Info de tamaño
        }
        else {
            TraceLog(LOG_ERROR, "ERROR: Archivo no encontrado - %s", filename.c_str());
            return Texture2D{};
        }
    }
    return textures[filename];
}

void ResourceManager::UnloadAll() {
    for (auto& texture : textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}
