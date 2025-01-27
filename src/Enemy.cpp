
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"


Enemy::Enemy(sf::Vector2f v)
{
    setSprite(v, "enemy");
}
// new comment

void Enemy::onCollision(Object& other) {
    other.handleCollisionWithEnemy(*this);
}

void Enemy::handleCollisionWithPlayer(Player& player)  {
    std::cout << "Enemy collided with Player! Attacking player.\n";
}
