#pragma once
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



class Wall : public StaticObject {
private:
  
public:
    Wall( sf::Vector2f v);

    void onCollision(Object& other);
    bool isAlive() const override;
    void setAlive(bool status) override;

};

