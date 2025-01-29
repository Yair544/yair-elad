#include "TextureManager.h"
#include <iostream>

// השגת המופע היחיד של המנהל
TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

// קונסטרקטור פרטי
TextureManager::TextureManager() = default;

// טעינת טקסטורה לפי שם ונתיב
void TextureManager::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;

        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    m_textures[name] = std::move(texture); // מוסיף את הטקסטורה למפה
}

// טעינת כל הטקסטורות מראש
void TextureManager::loadAllTextures() {
    std::vector<std::pair<std::string, std::string>> textures = {
        {"door", "door.jpg"},
        {"enemy", "enemy.png"},
        {"player", "player.jpg"},
        {"rock", "rock.png"},
        {"wall", "wall.jpg"},

        {"addLive", "addLive.png"},
        {"time", "time.png"},
        {"killEnemy", "killEnemy.png"},
        {"freeze", "freeze.png"},
    };

    for (const auto& [name, filePath] : textures) {
        loadTexture(name, filePath);
    }
}

// גישה לטקסטורה לפי שם
const sf::Texture& TextureManager::getTexture(const std::string& name) const {
    auto it = m_textures.find(name);
    if (it == m_textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}
