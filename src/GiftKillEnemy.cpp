
#include "GiftKillEnemy.h"


GiftKillEnemy::GiftKillEnemy(sf::Vector2f v)
{
    setSprite(v, "killEnemy");
}

//void GiftKillEnemy::onGiftCollision(Object& other, Controller& controller){
//    other.handleCollisionWithGift(*this, controller);
//}

void GiftKillEnemy::handleCollisionWithPlayer(Player& player, Controller& controller) {
    // משפיע על המשחק דרך Controller
    std::cout << "GiftAddLive" << std::endl;
    controller.killEnemy();
}