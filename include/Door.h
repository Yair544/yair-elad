#pragma once
#include "StaticObject.h"
#include "object.h"
#include "TextureManager.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



class Door : public StaticObject {
private:
    
public:
    Door( sf::Vector2f v);

    bool isAlive() const override;
    void setAlive(bool status) override;
    
};

