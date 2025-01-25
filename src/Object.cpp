#include "Object.h"

Object::Object() {}

void Object::setLocation(const sf::Vector2f& loc) { m_loc = loc;}

sf::Vector2f Object::getLocation() const {return m_loc;}

void Object::resizeSprite(float scaleSize)
{
    // קבלת הגבולות המקוריים של התמונה
    sf::FloatRect bounds = m_sprite.getLocalBounds();

    // חישוב קנה המידה
    float scaleX = scaleSize / bounds.width;
    float scaleY = scaleSize / bounds.height;

    // הגדרת קנה המידה
    m_sprite.setScale(scaleX, scaleY);
}

 void Object::setSprite(sf::Vector2f loc, std::string textureName)
{
    m_loc = loc;
    TextureManager& textureManager = TextureManager::getInstance();
    m_sprite = sf::Sprite(textureManager.getTexture(textureName));
    if (textureName == "player" || textureName == "enemy")
    {
        resizeSprite(Constants::MOVINGTILESIZE);
    }
    else
    {
        resizeSprite(Constants::TILESIZE);
    }
}

 void Object::draw(sf::RenderTarget& target)
 {
     m_sprite.setPosition(m_loc.x, m_loc.y);
     target.draw(m_sprite);
 }

 sf::FloatRect Object::getGlobalBounds() const{
     return m_sprite.getGlobalBounds();
 }

 void Object::onCollision(Object& other) {
     std::cout << "Object " << std::endl;
 }
