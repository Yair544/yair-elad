
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Door.h"


Door::Door(sf::Vector2f v)
{
    setSprite(v, "door");
}

bool Door::isAlive() const {
    return true;
}

void Door::setAlive(bool status) {
}
