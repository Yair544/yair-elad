
#include "GiftFreeze.h"

GiftFreeze::GiftFreeze(sf::Vector2f v)
{
    setSprite(v, "freeze");

}

void GiftFreeze::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // ����� �� ����� ��� Controller
    std::cout << "GiftFreeze" << std::endl;
}