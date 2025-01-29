#pragma once

#include "Gift.h"
#include <SFML/Graphics.hpp>

class GiftTime : public Gift {
private:
 
public:

    GiftTime(sf::Vector2f v);
  
    void handleCollisionWithPlayer(Player& player, Controller& controller) override;
};