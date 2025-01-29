#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>

//dgd
class Constants {
public:
    // Window properties
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 800;

    static constexpr float TOOLBARBUTTONWIDTH = 200;
    static constexpr float TOOLBARBUTTONHEIGHT = 200;

    static constexpr float TILESIZE = 50.f;
    static constexpr float MOVINGTILESIZE = 45.f;

    // Toolbar size
    static constexpr int TOOLBAR_SIZE = 8;
};