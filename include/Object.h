#pragma once
#include <string>
#include "Constants.h"
#include <TextureManager.h>
#include <SFML/Graphics.hpp>

class Object {
private:
    
    sf::Vector2f m_loc;
    sf::Sprite m_sprite;

public:
    Object();

    void setLocation(const sf::Vector2f& loc);
    
    sf::Vector2f getLocation() const;

    virtual void draw(sf::RenderTarget& target);

    virtual void resizeSprite(float scaleSize);

    virtual void setSprite(sf::Vector2f loc , std::string textureName);

    sf::FloatRect getGlobalBounds() const;

    virtual void onCollision(Object& other);
};
