#include "GameClock.h"



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

// ������� ���� ����� ��� ���� ��� ������ �������
float GameClock::getDeltaTime() {
    return m_clock.restart().asSeconds();
}

void GameClock::display(sf::RenderTarget& window, const sf::Font& font) const {
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::Green);
    timeText.setString("Time Left: " + std::to_string(static_cast<int>(m_timeLeft)) + "s");
    timeText.setPosition(200.f, 500.f);
    window.draw(timeText);
}

void GameClock::initClock(int time) {
    m_totalTime = time;
    m_timeLeft = 0;
    m_gameOver = false;
}