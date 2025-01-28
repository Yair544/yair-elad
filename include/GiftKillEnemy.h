#pragma once

#include "Gift.h"
#include <SFML/Graphics.hpp>
#include <Controller.h>

class GiftKillEnemy : public Gift {
private:

public:

    GiftKillEnemy(sf::Vector2f v);
    
    //void onGiftCollision(Object& other, Controller& controller) override;
    void handleCollisionWithPlayer(Player& player, Controller& controller) override;
};

