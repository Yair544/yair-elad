#pragma once

#include "Gift.h"
#include <SFML/Graphics.hpp>

class GiftAddLive : public Gift {
private:

public:
    
    GiftAddLive(sf::Vector2f v);
    
    void handleCollisionWithPlayer(Player& player, Controller& controller) override;
};

