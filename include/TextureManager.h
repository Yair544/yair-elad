#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

class TextureManager {
public:
    // ���� ����� ����� �� �����
    static TextureManager& getInstance();

    // ����� ������� ��� �� �����
    void loadTexture(const std::string& name, const std::string& filePath);

    // ����� �� ��������� ����
    void loadAllTextures();

    // ���� �������� ��� ��
    const sf::Texture& getTexture(const std::string& name) const;

private:
    // ���������� ���� ������ ����� ������
    TextureManager();

    // ����� ������ ����� ������
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

    // ��� ��������
    std::unordered_map<std::string, sf::Texture> m_textures;
};