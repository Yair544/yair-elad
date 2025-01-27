#pragma once
#include "UpdatingObject.h"
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Wall.h>



class Player : public UpdatingObject
{
private:
    int m_amount_life;

public:
    Player( sf::Vector2f v);

    void move(int speed, float deltatime, sf::Keyboard::Key key);

    void onCollision(Object& other) override;
    void handleCollisionWithWall(Wall& wall);
    void handleCollisionWithEnemy(Enemy & enemy) override;

    int getAmountLife() const;
    void setAmountLife(int amount);
};

