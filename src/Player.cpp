#include "Player.h"

#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

Player::Player(sf::Vector2f v)
{
    setSprite(v, "player");
    this->setAmountLife(5);
}


void Player::move(int speed, float deltaTime, sf::Keyboard::Key key)
{
    sf::Vector2f loc=getLocation();

    switch (key)
    {
    case sf::Keyboard::Right:
        loc.x += speed * deltaTime;
        setLocation(loc);
        break;
    case sf::Keyboard::Left:
        loc.x -= speed * deltaTime;
        setLocation(loc);
        break;
    case sf::Keyboard::Up:
        loc.y -= speed * deltaTime;
        setLocation(loc);
        break;
    case sf::Keyboard::Down:
        loc.y += speed * deltaTime;
        setLocation(loc);
        break;
    default:
        break;
    }
}

void Player::onCollision(Object& other) {
    other.handleCollisionWithPlayer(*this);
}

void Player::onCollision(Object& other, Controller& controller) {
    other.handleCollisionWithPlayer(*this, controller);
}

void Player::handleCollisionWithWall(Wall& wall) {
    std::cout << "Player collided with a Wall! Stopping movement.\n";
}

void Player::handleCollisionWithEnemy(Enemy& enemy) {
    std::cout << "Player collided with an Enemy! Losing life.\n";
}

void Player::handleCollisionWithGift(Gift gift)
{
    gift.setAlive(false);
}

int Player::getAmountLife() const {
    return m_amount_life;
}

void Player::setAmountLife(int amount) {
    m_amount_life = amount;
}

void Player::addLife() {
    m_amount_life++;
}