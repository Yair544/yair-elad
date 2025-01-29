#include "Controller.h"
#include "Object.h"
#include "staticObject.h"
#include "UpdatingObject.h"
#include "Wall.h"
#include "Enemy.h"
#include "Door.h"
#include "Rock.h"
#include "Player.h"
#include "Gift.h"
#include "GiftAddLive.h"
#include "GiftFreeze.h"
#include "GiftKillEnemy.h"
#include "GiftTime.h"
#include <iostream>
#include <Constants.h>
#include <string>
#include <TextureManager.h>
#include <GameClock.h>

//-----------------------------------------------------------------------------
// Starts the game, initializes the window, loads textures, and runs the game loop.
void Controller::startGame()
{
    //set window
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Board and Button Example");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    //set singletone of textureManager
    TextureManager& textureManager = TextureManager::getInstance();
    try {
        textureManager.loadAllTextures();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    //load files
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

    //load levels
    std::vector<std::string> levelByChars;
    //std::vector<std::unique_ptr<Object>> allObject;
    

    int rows;
    int cols;
    loadLevelToStringVector(currLevel, levelByChars, rows, cols);

    for (const auto& line : levelByChars) { std::cout << line << std::endl; }

    loadAllObjectToVector(levelByChars, m_updatingObjects, m_staticObjects);
    drawAllObject(m_updatingObjects, m_staticObjects, window);

    Player* player = getPointerToPlayer(m_updatingObjects);

    //set speed and clock
    const float playerSpeed = 200.f;
    const float enemySpeed = 10.f;

    // מהירות תנועה בפיקסלים לשנייה
    const float speed = 200.f;

    // לולאת המשחק
    window.setFramerateLimit(60);
    GameClock gameClock(65.f);
    float enemyTimer = 0.f;
    const float moveInterval = 0.5f;
    sf::Clock deltaClock;

    //GAME LOOP
    while (window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        gameClock.update();
        if (gameClock.isGameOver()) {
            std::cout << "Game Over! Time's up.\n";
            break;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                playlist.close();
                exit(EXIT_SUCCESS);
            }
        }

        //player and enemy movment
        for (sf::Keyboard::Key key : {sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down})
        {
            if (sf::Keyboard::isKeyPressed(key)) {
                player->move(playerSpeed, deltaTime, key, m_staticObjects);
            }
        }

        for (auto& obj : m_updatingObjects)
        {
            if (Enemy* enemy = dynamic_cast<Enemy*>(obj.get())) {
                enemy->move(enemySpeed, deltaTime, player->getLocation(), m_updatingObjects, m_staticObjects);
            }
        }

        checkAllCollisions(m_updatingObjects, m_staticObjects);

        window.clear();
        drawAllObject(m_updatingObjects, m_staticObjects, window);
        displayInfo(window, gameClock, font, player->getAmountLife(), level_name);
        window.display();
    }
}

//-----------------------------------------------------------------------------
// Placeholder function to handle enemy killing logic.
void Controller::killEnemy() {
    std::cout << "aaaaaa" << std::endl;
}


//-----------------------------------------------------------------------------
// Loads the level from a file into a vector of strings.
void Controller::loadLevelToStringVector(std::ifstream& file, std::vector<std::string>& levelByChars, int& rows, int& cols) {
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
// Loads all objects from the level vector into updating and static object vectors.
void Controller::loadAllObjectToVector(const std::vector<std::string>& levelByChars,
    std::vector<std::unique_ptr<UpdatingObject>>& updatingObject,
    std::vector<std::unique_ptr<StaticObject>>& staticObjects)
{

    updatingObject.clear();
    staticObjects.clear();

    for (size_t row = 0; row < levelByChars.size(); ++row) {
        
        for (size_t col = 0; col < levelByChars[row].size(); ++col) {
            char ch = levelByChars[row][col];
            sf::Vector2f position(col * Constants::TILESIZE, (row + 1) * Constants::TILESIZE);
            switch (ch)
            {
            case '!':
                updatingObject.push_back(std::make_unique<Enemy>(position));
                break;
            case '\\':
                updatingObject.push_back(std::make_unique<Player>(position, this));
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
// Draws all updating and static objects to the window.
void Controller::drawAllObject(std::vector<std::unique_ptr<UpdatingObject>>& updatingObject,
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
// Returns a pointer to the player object from the updating objects vector.
Player* Controller::getPointerToPlayer(std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects) {
    for (auto& obj : updatingObjects)
    {
            //type check
        if (Player* player = dynamic_cast<Player*>(obj.get())) {
            return player;
        }
    }
    exit(EXIT_FAILURE);
}

//-----------------------------------------------------------------------------
// Checks for collisions between updating and static objects, and handles them.
void Controller::checkAllCollisions(
    std::vector<std::unique_ptr<UpdatingObject>>& updatingObjects,
    std::vector<std::unique_ptr<StaticObject>>& staticObjects) {
    for (auto& movingObj : updatingObjects) {
        if (!movingObj) continue;

        for (auto& staticObj : staticObjects) {
            if (!staticObj) continue;
            if (auto* gift = dynamic_cast<Gift*>(staticObj.get())) {
                if (movingObj->getGlobalBounds().intersects(staticObj->getGlobalBounds())) {
                    movingObj->onCollision(*staticObj, *this);
                    gift->onCollision(*movingObj, *this);
                }
            }
            // בדיקת התנגשות בין נע לסטטי
            else if (movingObj->getGlobalBounds().intersects(staticObj->getGlobalBounds())) {
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

//-----------------------------------------------------------------------------
// Displays game information (time left, lives, level) on the window.
void Controller::displayInfo(sf::RenderWindow& window, const GameClock& clock, sf::Font& font, int lives, const std::string& levelName) {
    // Display time left
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    if (static_cast<int>(clock.getTimeLeft()) > 60) {
        timeText.setFillColor(sf::Color::Green);
    }
    else {
        timeText.setFillColor(sf::Color::Red);
    }
    timeText.setString("Time Left: " + std::to_string(static_cast<int>(clock.getTimeLeft())) + "s");
    timeText.setPosition(10.f, 10.f);
    window.draw(timeText);

    // Display lives
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::Blue);
    livesText.setString("Lives: " + std::to_string(lives));
    livesText.setPosition(250.f, 10.f); // Adjust position for more space
    window.draw(livesText);

    // Display level name
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setString(levelName.substr(0, levelName.size() - 4));
    levelText.setPosition(450.f, 10.f); // Adjust position for more space
    window.draw(levelText);

    
}

//-----------------------------------------------------------------------------
// reset game is player killed
void Controller::resetGame() {

    for (auto& obj : m_updatingObjects)
    {
        obj->setLocation(obj->getStartLocation());    
    }  
}




