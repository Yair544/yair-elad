
#include "GiftTime.h"


GiftTime::GiftTime(sf::Vector2f v)
{
    setSprite(v, "time");

}

void GiftTime::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // משפיע על המשחק דרך Controller
    std::cout << "GiftTime" << std::endl;
    controller.addTime(5);
}

