
#include "GiftAddLive.h"


GiftAddLive::GiftAddLive(sf::Vector2f v)
{
    setSprite(v, "addLive");
}

void GiftAddLive::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // ����� �� ����� ��� Controller
    std::cout << "GiftAddLive" << std::endl;
}

