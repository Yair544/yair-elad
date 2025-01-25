
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Player.h"


Player::Player(sf::Vector2f v)
{
    setSprite(v, "player");
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

void Player::onCollision(Object& other){
    std::cout << "player " << std::endl;
}



