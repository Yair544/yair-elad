#pragma once

#include <SFML/Graphics.hpp>
class GameClock {
private:
    sf::Clock m_clock;       // שעון למדידת זמן שחלף
    float m_totalTime;       // הזמן הכולל של המשחק
    float m_timeLeft;        // הזמן שנותר למשחק
    bool m_gameOver = false; // מציין אם המשחק נגמר

public:
    // קונסטרקטור לקבלת זמן כולל (בשניות)
    GameClock(float totalTime);
    GameClock() = default;

    // עדכון השעון (חישוב הזמן שנותר)
    void update();

    // הוספת זמן לשעון
    void addTime(float seconds);

    // החזרת הזמן שנותר (בשניות)
    float getTimeLeft() const;

    // בדיקה אם הזמן נגמר
    bool isGameOver() const;
};
