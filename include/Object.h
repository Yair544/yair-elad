#pragma once
#include <string>
#include "Constants.h"
#include <TextureManager.h>
#include <SFML/Graphics.hpp>

// Forward declarations
class Controller;
class Player;
class Enemy;
class Wall;
class Gift;

class Object {
private:

    sf::Vector2f m_startLocation;
    sf::Vector2f m_loc;
    sf::Sprite m_sprite;
    bool m_alive;

public:
    Object();
    virtual ~Object() = default;

    void setStartLocation(const sf::Vector2f& loc);

    sf::Vector2f getStartLocation();

    void setLocation(const sf::Vector2f& loc);

    sf::Vector2f getLocation() const;

    virtual void draw(sf::RenderTarget& target);

    virtual void resizeSprite(float scaleSize);

    virtual void setSprite(sf::Vector2f loc, std::string textureName);

    sf::FloatRect getGlobalBounds() const;

    virtual bool isAlive() const;

    virtual void setAlive(bool status);

    virtual void onCollision(Object& other);
    virtual void onCollision(Object& other, Controller& controller);
    virtual void handleCollisionWith(Object& other);
    virtual void handleCollisionWith(Object& other, Controller& controller);
    virtual void handleCollisionWithPlayer(class Player& player);
    virtual void handleCollisionWithPlayer(class Player& player, Controller& controller);
    virtual void handleCollisionWithEnemy(class Enemy& enemy);
    virtual void handleCollisionWithWall(class Wall& wall);
    virtual void handleCollisionWithGift(class Gift& gift, Controller& controller);

};
