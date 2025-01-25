#pragma once

#include <SFML/Graphics.hpp>

class Button {
private:
    float m_x, m_y;          // Button position
    float m_width, m_height; // Button size
    const sf::Texture* m_texture; // Pointer to the button texture
    float m_borderThickness;      // Border thickness
    char m_icon = ' ';            // Icon character
    bool m_isHighlighted = false; // Highlight state (red background)

public:
    // Default constructor
    Button() = default;

    // Constructor
    Button(float x, float y, float width, float height, const sf::Texture* texture, float borderThickness = 2.f);

    // Check if the button is clicked
    bool isClicked(float mouseX, float mouseY) const;

    // Set highlight state
    void setHighlight(bool highlight);

    // Draw the button
    void draw(sf::RenderWindow& window) const;

    // Set button position
    void setPosition(float x, float y);

    // Set button size
    void setSize(float width, float height);

    // Get button size
    void getSize(float& width, float& height) const;

    // Set border thickness
    void setBorderThickness(float thickness);

    // Set button texture
    void setTexture(const sf::Texture* texture);

    // Get the pointer to the button texture
    const sf::Texture* getTexture() const;

    // Get button position
    void getPosition(float& x, float& y) const;

    // Set the icon character
    void setIcon(char icon);

    // Get the icon character
    char getIcon() const;
};