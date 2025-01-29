#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
#include "UpdatingObject.h"
#include "StaticObject.h"
#include <GameClock.h>


class Controller {
private:
    std::vector<std::unique_ptr<UpdatingObject>> m_updatingObjects;
    std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
    GameClock m_clock;

public:
    void startGame();
    void checkAllCollisions(
        std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
        std::vector<std::unique_ptr<StaticObject>>& staticObjects);
    void killEnemy();
    void addTime(int time);
};
