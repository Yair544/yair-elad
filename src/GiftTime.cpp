
#include "GiftTime.h"


GiftTime::GiftTime(sf::Vector2f v)
{
    setSprite(v, "time");

}

void GiftTime::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // ����� �� ����� ��� Controller
    std::cout << "GiftTime" << std::endl;
    controller.addTime(5);
}

