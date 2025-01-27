#pragma once
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include "UpdatingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



class Enemy : public UpdatingObject {
private:

public:
    Enemy(sf::Vector2f v);

    void onCollision(Object& other) override;
    void handleCollisionWithPlayer(Player& player);

};