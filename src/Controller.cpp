#include "Controller.h"
#include "Object.h"
#include "Wall.h"
#include "Enemy.h"
#include "Door.h"
#include "Rock.h"
#include "UpdatingObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Gift.h"
#include "GiftAddLive.h"
#include "GiftFreeze.h"
#include "GiftKillEnemy.h"
#include "GiftTime.h"
#include <iostream>
#include <Constants.h>
#include <fstream>
#include <string>
#include <TextureManager.h>
#include <SFML/Graphics.hpp>
#include <GameClock.h>

//-------------------------------prototype---------------------------------------
void loadLevelToStringVector(std::ifstream& file, std::vector<std::string>& levelByChars, int& rows, int& cols);

void loadAllObjectToVector(const std::vector<std::string>& levelByChars,
    std::vector<std::unique_ptr<UpdatingObject>> &updatingObject,
    std::vector<std::unique_ptr<StaticObject>> &staticObjects);

void drawAllObject(std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    std::vector<std::unique_ptr<StaticObject>>& staticObjects,
    sf::RenderTarget& window);

Player* getPointerToPlayer(std::vector<std::unique_ptr<UpdatingObject>>& updatingObject);

void checkAllCollisions(
    std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    std::vector<std::unique_ptr<StaticObject>>& staticObjects);

void displayTime(sf::RenderWindow& window, const GameClock& clock, sf::Font& font);

//start
void Controller::startGame()
{
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Board and Button Example");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    //load texture to singleton
    TextureManager& textureManager = TextureManager::getInstance();
    try {
        textureManager.loadAllTextures();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    //!!!!!!!!!check closing!!!!
   
    //loading levels file
    std::ifstream playlist("playlist.txt");
    if (!playlist.is_open())
    {
        std::cerr << "Could not open playlist.txt" << std::endl;
        return;
    }

    std::string level_name;
    std::getline(playlist, level_name);
    std::cout << level_name << "\n";

    std::ifstream currLevel(level_name);
    if (!currLevel.is_open())
    {
        std::cerr << "Could not open currLevel" << std::endl;
        return;
    }

    //load file to vector
    std::vector<std::string> levelByChars;
    //std::vector<std::unique_ptr<Object>> allObject;
    std::vector<std::unique_ptr<UpdatingObject>> updatingObjects;
    std::vector<std::unique_ptr<StaticObject>> staticObjects;
    int rows;
    int cols;
    loadLevelToStringVector(currLevel, levelByChars, rows, cols);

    for (const auto& line : levelByChars) { std::cout << line << std::endl; } //print file
        
    loadAllObjectToVector(levelByChars, updatingObjects, staticObjects);
    drawAllObject(updatingObjects, staticObjects, window);

    Player* player = getPointerToPlayer(updatingObjects);
   
    // יצירת שעון
    sf::Clock clock;

    // מהירות תנועה בפיקסלים לשנייה
    const float speed = 200.f;

    // לולאת המשחק
    window.setFramerateLimit(60);
    GameClock gameClock(60.f); // שעון עם 60 שניות למשחק
    float enemyTimer = 0.f;
    const float moveInterval = 0.5f; // תזוזה כל 0.5 שניות
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        // עדכון השעון
        gameClock.update();
        // בדיקת מצב המשחק
        if (gameClock.isGameOver()) {
            std::cout << "Game Over! Time's up.\n";
            break;
        }

        // טיפול באירועים
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                playlist.close();
                exit(EXIT_SUCCESS);
            }
        }

        // תזוזה של האובייקט באמצעות מקשים לחוצים
        for (sf::Keyboard::Key key : {sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down})
        {
            if (sf::Keyboard::isKeyPressed(key)) {
                player->move(speed, deltaTime, key);
            }   
        }

        checkAllCollisions(updatingObjects, staticObjects);

        window.clear();
        drawAllObject(updatingObjects, staticObjects, window);
        displayTime(window, gameClock, font);
        window.display();
    }
}


//-----------------------------------------------------------------------------
//loadLevelToStringVector
void loadLevelToStringVector(std::ifstream& file, std::vector<std::string>& levelByChars, int& rows, int& cols) {
    
    std::string line;
    rows = 0;
    cols = 0;

    levelByChars.clear(); 

    while (std::getline(file, line))
    {
        if (cols == 0) {
            cols = line.size(); 
        }
        levelByChars.push_back(line);  
        rows++; 
    }
}

//-----------------------------------------------------------------------------
//load All Object To Vector
void loadAllObjectToVector(const std::vector<std::string>& levelByChars,
        std::vector<std::unique_ptr<UpdatingObject>> &updatingObject,
        std::vector<std::unique_ptr<StaticObject>> &staticObjects)
 {

    updatingObject.clear();
    staticObjects.clear();

    for (size_t row = 0; row < levelByChars.size(); ++row) {
        
        for (size_t col = 0; col < levelByChars[row].size(); ++col) {
            char ch = levelByChars[row][col];
            sf::Vector2f position(col * Constants::TILESIZE, row * Constants::TILESIZE);
            switch (ch) 
            {
            case '!':
                updatingObject.push_back(std::make_unique<Enemy>(position));
                break;
            case '\\':

                updatingObject.push_back(std::make_unique<Player>(position));
                break;
            case '#':
                staticObjects.push_back(std::make_unique<Wall>(position));
                break;
            case '@':
                staticObjects.push_back(std::make_unique<Rock>(position));
                break;
            case 'D':
                staticObjects.push_back(std::make_unique<Door>(position));
                break;
            case 'a':
                staticObjects.push_back(std::make_unique<GiftAddLive>(position));
                break;
            case 'f':
                staticObjects.push_back(std::make_unique<GiftFreeze>(position));
                break;
            case 'k':
                staticObjects.push_back(std::make_unique<GiftKillEnemy>(position));
                break;
            case 't':
                staticObjects.push_back(std::make_unique<GiftTime>(position));
                break;
            default:
                break;
            }
        }   
    }
}

//-----------------------------------------------------------------------------
//print all object
void drawAllObject( std::vector<std::unique_ptr<UpdatingObject>>  & updatingObject,
            std::vector<std::unique_ptr<StaticObject>>& staticObjects,
             sf::RenderTarget& window)
{
    for (int i = 0; i < staticObjects.size(); i++)
    {
        staticObjects[i]->draw(window);
    }
    for (int i = 0; i < updatingObject.size(); i++)
    {
        updatingObject[i]->draw(window);
    }

  
}

//-----------------------------------------------------------------------------
//return Pointer To Player
Player* getPointerToPlayer(std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects) {
    for (auto& obj : updatingObjects)
    { 
            //type check
            if (Player* player = dynamic_cast<Player*>(obj.get())) {
                return player; 
            }   
    }
    exit(EXIT_FAILURE);  //no player, no game!
    
}

//-----------------------------------------------------------------------------
void checkAllCollisions(
    std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    std::vector<std::unique_ptr<StaticObject>>& staticObjects) {

    // בדיקת התנגשויות בין אובייקטים נעים לאובייקטים סטטיים
    for (auto& movingObj : updatingObjects) {
        if (!movingObj) continue;

        for (auto& staticObj : staticObjects) {
            if (!staticObj) continue;

            // בדיקת התנגשות בין נע לסטטי
            if (movingObj->getGlobalBounds().intersects(staticObj->getGlobalBounds())) {
                movingObj->onCollision(*staticObj);
                staticObj->onCollision(*movingObj);
            }
        }
    }

    // בדיקת התנגשויות בין אובייקטים נעים
    for (size_t i = 0; i < updatingObjects.size(); ++i) {
        if (!updatingObjects[i]) continue;

        UpdatingObject& obj1 = *updatingObjects[i];

        for (size_t j = i + 1; j < updatingObjects.size(); ++j) {
            if (!updatingObjects[j]) continue;

            UpdatingObject& obj2 = *updatingObjects[j];

            // בדיקת התנגשות בין שני אובייקטים נעים
            if (obj1.getGlobalBounds().intersects(obj2.getGlobalBounds())) {
                obj1.onCollision(obj2);
                obj2.onCollision(obj1);
            }
        }
    }

    // מחיקת אובייקטים שנהרסו
    updatingObjects.erase(
        std::remove_if(
            updatingObjects.begin(),
            updatingObjects.end(),
            [](const std::unique_ptr<UpdatingObject>& obj) {
                return obj && !obj->isAlive();
            }),
        updatingObjects.end());

    // מחיקת אובייקטים שנהרסו
    staticObjects.erase(
        std::remove_if(
            staticObjects.begin(),
            staticObjects.end(),
            [](const std::unique_ptr<StaticObject>& obj) {
                return obj && !obj->isAlive();
            }),
        staticObjects.end());
}

void displayTime(sf::RenderWindow& window, const GameClock& clock, sf::Font& font) {
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::Green);
    timeText.setString("Time Left: " + std::to_string(static_cast<int>(clock.getTimeLeft())) + "s");
    timeText.setPosition(200.f, 500.f);
    window.draw(timeText);
}
