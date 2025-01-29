#pragma once

#include <SFML/Graphics.hpp>
class GameClock {
private:
    sf::Clock m_clock;       // ���� ������ ��� ����
    float m_totalTime;       // ���� ����� �� �����
    float m_timeLeft;        // ���� ����� �����
    bool m_gameOver = false; // ����� �� ����� ����

public:
    GameClock() = default;

    // ����� ����� (����� ���� �����)
    void update();

    void initClock(int time);

    // ����� ��� �����
    void addTime(float seconds);

    // ����� ���� ����� (������)
    float getTimeLeft() const;

    // ����� �� ���� ����
    bool isGameOver() const;

    float getDeltaTime();

    void display(sf::RenderTarget& window, const sf::Font& font) const;

};
