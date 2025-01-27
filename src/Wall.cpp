#include "Player.h"
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Wall.h"


Wall::Wall(sf::Vector2f v)
{
    setSprite(v, "wall");

}

void Wall::onCollision(Object& other) {
    other.handleCollisionWithWall(*this);
}

void Wall::handleCollisionWithPlayer(Player& player) {
}

bool Wall::isAlive() const {
    return true;
}

void Wall::setAlive(bool status){
}

