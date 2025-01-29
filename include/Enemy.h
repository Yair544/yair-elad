#pragma once
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include "UpdatingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Wall.h"
#include "Rock.h"



class Enemy : public UpdatingObject {
private:

public:
    Enemy(sf::Vector2f v);

    void onCollision(Object& other) override;
    void handleCollisionWithPlayer(Player& player);
    void move(float speed, float deltatime, sf::Vector2f playerLocation,
        const  std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
        const std::vector<std::unique_ptr<StaticObject>>& staticObjects);
    bool checkPotentialMove(const sf::Vector2f& movement,
        const std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
        const std::vector<std::unique_ptr<StaticObject>>& staticObjects);

};