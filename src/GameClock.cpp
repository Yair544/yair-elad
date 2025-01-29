#include "GameClock.h"

// קונסטרקטור
GameClock::GameClock(float totalTime) : m_totalTime(totalTime), m_timeLeft(totalTime) {}

// עדכון זמן
void GameClock::update() {
    sf::Time elapsed = m_clock.getElapsedTime();
    m_timeLeft = m_totalTime - elapsed.asSeconds();
    if (m_timeLeft <= 0) {
        m_timeLeft = 0;
        m_gameOver = true;
    }
}

// הוספת זמן
void GameClock::addTime(float seconds) {
    m_totalTime += seconds;
}

// זמן שנותר
float GameClock::getTimeLeft() const {
    return m_timeLeft;
}

// בדיקה אם המשחק נגמר
bool GameClock::isGameOver() const {
    return m_gameOver;
}
