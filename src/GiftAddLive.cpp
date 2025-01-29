
#include "GiftAddLive.h"


GiftAddLive::GiftAddLive(sf::Vector2f v)
{
    setSprite(v, "addLive");
}

void GiftAddLive::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // משפיע על המשחק דרך Controller
    std::cout << "GiftAddLive" << std::endl;
}

