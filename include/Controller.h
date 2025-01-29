
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "staticObject.h"
#include "UpdatingObject.h"

class UpdatingObject;
class StaticObject;
class GameClock;
class Player;

class Controller {
public:
    void startGame();
    void resetGame();  //??
    void killEnemy();
    

private:
    std::vector<std::unique_ptr<UpdatingObject>> m_updatingObjects;
    std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
    sf::Clock m_clock;

    void displayInfo(sf::RenderWindow& window, const GameClock& clock, sf::Font& font, int lives, const std::string& levelName);
    void loadLevelToStringVector(std::ifstream& file, std::vector<std::string>& levelByChars, int& rows, int& cols);
    void loadAllObjectToVector(const std::vector<std::string>& levelByChars,
        std::vector<std::unique_ptr<UpdatingObject>>& updatingObject,
        std::vector<std::unique_ptr<StaticObject>>& staticObjects);
    void drawAllObject(std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
        std::vector<std::unique_ptr<StaticObject>>& staticObjects,
        sf::RenderTarget& window);
    Player* getPointerToPlayer(std::vector<std::unique_ptr<UpdatingObject>>& updatingObject);
    void checkAllCollisions(
        std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
        std::vector<std::unique_ptr<StaticObject>>& staticObjects);
    
};

