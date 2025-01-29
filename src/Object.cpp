#include "Object.h"
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Gift.h"
#include "TextureManager.h"
#include "Constants.h"

Object::Object() {}

void Object::setStartLocation(const sf::Vector2f& loc) { m_startLocation = loc; }

sf::Vector2f Object::getStartLocation() {return m_startLocation; }

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

 bool Object::isAlive() const {
     return m_alive;
 }

 void Object::setAlive(bool status) {
     m_alive = status;
 }




 void Object::onCollision(Object& other) {
     other.handleCollisionWith(*this);
 }
 void Object::onCollision(Object& other, Controller& controller) {
     other.handleCollisionWith(*this, controller);
 }
 // פונקציות להתנגשות עם סוגים ספציפיים
  void Object::handleCollisionWith(Object& other) {
      
  }
  void Object::handleCollisionWith(Object& other, Controller& controller) {
      
  }
  void Object::handleCollisionWithPlayer(class Player& player) {}
  void Object::handleCollisionWithPlayer(class Player& player, Controller& controller) {};
  void Object::handleCollisionWithEnemy(class Enemy& enemy) {}
  void Object::handleCollisionWithWall(class Wall& wall) {}
  void Object::handleCollisionWithGift(class Gift& wall, Controller& controller) {};
