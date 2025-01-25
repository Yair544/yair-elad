#pragma once
#include "UpdatingObject.h"
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



class Player : public UpdatingObject
{
private:
 

public:
    Player( sf::Vector2f v);

    void move(int speed, float deltatime, sf::Keyboard::Key key);

    void onCollision(Object& other);
};

