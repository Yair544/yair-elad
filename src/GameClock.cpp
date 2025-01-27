#include "GameClock.h"

// ����������
GameClock::GameClock(float totalTime) : m_totalTime(totalTime), m_timeLeft(totalTime) {}

// ����� ���
void GameClock::update() {
    sf::Time elapsed = m_clock.getElapsedTime();
    m_timeLeft = m_totalTime - elapsed.asSeconds();
    if (m_timeLeft <= 0) {
        m_timeLeft = 0;
        m_gameOver = true;
    }
}

// ����� ���
void GameClock::addTime(float seconds) {
    m_totalTime += seconds;
}

// ��� �����
float GameClock::getTimeLeft() const {
    return m_timeLeft;
}

// ����� �� ����� ����
bool GameClock::isGameOver() const {
    return m_gameOver;
}
