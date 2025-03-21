#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <map>
#include <string>

class ResourceManager {
private:
    std::map<std::string, Texture2D> textures;
    std::map<std::string, Sound> sounds;
    
public:
    ResourceManager();
    ~ResourceManager();
    
    // Texture methods
    void LoadTexture(const std::string& name, const std::string& filename);
    Texture2D GetTexture(const std::string& name) const;
    void UpdateTexture(const std::string& name, Texture2D texture);
    
    // Sound methods
    void LoadSound(const std::string& name, const std::string& filename);
    Sound GetSound(const std::string& name) const;
};

#endif // RESOURCE_MANAGER_H