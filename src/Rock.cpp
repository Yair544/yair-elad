
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Rock.h"


Rock::Rock(sf::Vector2f v)
{
    setSprite(v, "rock");


}


