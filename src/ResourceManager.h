#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <string>
#include "raylib.h"

class ResourceManager {
public:
    static Texture2D LoadTexture(const std::string& filename);
    static void UnloadAll();
private:
    static std::unordered_map<std::string, Texture2D> textures;
};

#endif
