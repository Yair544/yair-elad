
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"


Enemy::Enemy(sf::Vector2f v)
{
    setStartLocation(v);
    setSprite(v, "enemy");
}
// new comment

void Enemy::onCollision(Object& other) {
    other.handleCollisionWithEnemy(*this);
}

void Enemy::handleCollisionWithPlayer(Player& player)  {
    std::cout << "Enemy collided with Player! Attacking player.\n";


}

void Enemy::move(float speed, float deltatime, sf::Vector2f playerLocation,
    const  std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    const std::vector<std::unique_ptr<StaticObject>>& staticObjects)
{
    sf::Vector2f movement(0.f, 0.f);
    if (playerLocation.x > getLocation().x) {
        movement.x += speed * deltatime;
    }
    else if (playerLocation.x < getLocation().x) {
        movement.x -= speed * deltatime;
    }
    if (playerLocation.y > getLocation().y) {
        movement.y += speed * deltatime;
    }
    else if (playerLocation.y < getLocation().y) {
        movement.y -= speed * deltatime;
    }

    if (checkPotentialMove(movement, updatingObjects, staticObjects)) {
        setLocation({ getLocation().x + movement.x, getLocation().y + movement.y });
    }
    else {
        // Try vertical movement if horizontal is blocked
        sf::Vector2f verticalMovement(0.f, movement.y);
        if (checkPotentialMove(verticalMovement, updatingObjects, staticObjects)) {
            setLocation({ getLocation().x, getLocation().y + verticalMovement.y });
        }
        else {
            // Try horizontal movement if vertical is blocked
            sf::Vector2f horizontalMovement(movement.x, 0.f);
            if (checkPotentialMove(horizontalMovement, updatingObjects, staticObjects)) {
                setLocation({ getLocation().x + horizontalMovement.x, getLocation().y });
            }
        }
    }
}


bool Enemy::checkPotentialMove(const sf::Vector2f& movement,
    const std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    const std::vector<std::unique_ptr<StaticObject>>& staticObjects) {
    sf::FloatRect potentialBounds = getGlobalBounds();
    potentialBounds.left += movement.x;
    potentialBounds.top += movement.y;

    for (const auto& obj : staticObjects) {
        if (typeid(*obj) == typeid(Wall) || typeid(*obj) == typeid(Rock)) {
            if (potentialBounds.intersects(obj->getGlobalBounds())) {
                return false;
            }
        }
    }

    for (const auto& obj : updatingObjects) {
        if (typeid(*obj) == typeid(Enemy) && obj.get() != this) {
            if (potentialBounds.intersects(obj->getGlobalBounds())) {
                return false;
            }
        }
    }

    return true;
}
