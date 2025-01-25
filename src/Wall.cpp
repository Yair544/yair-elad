
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
    std::cout << "wall " << std::endl;
}



