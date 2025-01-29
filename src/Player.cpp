
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Controller.h"



Player::Player(sf::Vector2f v, Controller* controller)
{
    setStartLocation(v);
    setSprite(v, "player");
    this->setAmountLife(5);
    m_controller = controller;
}


void Player::move(float speed, float deltaTime, sf::Keyboard::Key key,
    const std::vector<std::unique_ptr<StaticObject>>& staticObjects) {

    sf::Vector2f movement(0.f, 0.f);
    switch (key) {
    case sf::Keyboard::Right:
        movement.x += speed * deltaTime;
        break;
    case sf::Keyboard::Left:
        movement.x -= speed * deltaTime;
        break;
    case sf::Keyboard::Up:
        movement.y -= speed * deltaTime;
        break;
    case sf::Keyboard::Down:
        movement.y += speed * deltaTime;
        break;
    default:
        break;
    }

    // stop moving if collision with wall or rock
    sf::FloatRect potentialBounds = getGlobalBounds();
    potentialBounds.left += movement.x;
    potentialBounds.top += movement.y;

    for (const auto& obj : staticObjects) {
        if (typeid(*obj) == typeid(Wall) || typeid(*obj) == typeid(Rock))
        {
            if (potentialBounds.intersects(obj->getGlobalBounds()))
            {

                std::cout << "collision with: " << typeid(*obj).name() << std::endl;
                std::cout << "dont move!!!!!!!!!! " << std::endl;
                return;
            }
        }
    }

    //movment if not collision
    setLocation({ getLocation().x + movement.x,getLocation().y + movement.y });


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
    m_amount_life--;

    std::cout << "Player collided with an Enemy! Losing life.\n";
    if (m_amount_life <= 0) {
        std::cout << "Game Over! Player has no more lives.\n";
        exit(EXIT_SUCCESS); 
    }
    else {
        m_controller->resetGame();  
    }
}

int Player::getAmountLife() const {
    return m_amount_life;
}

void Player::setAmountLife(int amount) {
    m_amount_life = amount;
}

