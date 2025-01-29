#include "Gift.h"


Gift::Gift(){}
   
//void Gift::onCollision(Object& other) {}
//
void Gift::onCollision(Object& other) {
	other.handleCollisionWithGift(*this);
}
//
//void Gift::handleCollisionWithPlayer(Player& other, Controller& controller) {
//	other.handleCollisionWithPlayer(*this, controller);
//}
