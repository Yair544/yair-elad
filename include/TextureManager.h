#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

class TextureManager {
public:
    // השגת המופע היחיד של המנהל
    static TextureManager& getInstance();

    // טעינת טקסטורה לפי שם ונתיב
    void loadTexture(const std::string& name, const std::string& filePath);

    // טעינת כל הטקסטורות מראש
    void loadAllTextures();

    // גישה לטקסטורה לפי שם
    const sf::Texture& getTexture(const std::string& name) const;

private:
    // קונסטרקטור פרטי למניעת יצירת מופעים
    TextureManager();

    // מחיקת פעולות העתקה והעברה
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

    // מפת טקסטורות
    std::unordered_map<std::string, sf::Texture> m_textures;
};