#pragma once
#include "UpdatingObject.h"
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Wall.h>
#include <Rock.h>



class Player : public UpdatingObject
{
private:
    int m_amount_life;
    Controller* m_controller;

public:
    Player( sf::Vector2f v, Controller* controller);

    void move(float speed, float deltaTime, sf::Keyboard::Key key,
        const std::vector<std::unique_ptr<StaticObject>>& staticObjects);

    void onCollision(Object& other) override;
    void onCollision(Object& other, Controller& controller);
    void handleCollisionWithWall(Wall& wall);
    void handleCollisionWithEnemy(Enemy & enemy) override;

    int getAmountLife() const;
    void setAmountLife(int amount);
};

