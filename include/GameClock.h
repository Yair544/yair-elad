#pragma once

#include <SFML/Graphics.hpp>
class GameClock {
private:
    sf::Clock m_clock;       // ���� ������ ��� ����
    float m_totalTime;       // ���� ����� �� �����
    float m_timeLeft;        // ���� ����� �����
    bool m_gameOver = false; // ����� �� ����� ����

public:
    // ���������� ����� ��� ���� (������)
    GameClock(float totalTime);
    GameClock() = default;

    // ����� ����� (����� ���� �����)
    void update();

    // ����� ��� �����
    void addTime(float seconds);

    // ����� ���� ����� (������)
    float getTimeLeft() const;

    // ����� �� ���� ����
    bool isGameOver() const;
};
