#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "IButton.h"

class Button : public IButton {
public:
    Button(float x, float y, float width, float height, sf::Font& font, const std::string& text);

    void update(const sf::Vector2i& mousePos, const sf::Event& event) override;
    void draw(sf::RenderWindow& window) override;
    bool isReleased() override;
    float getWidth() const;
    float getHeight() const;
    void setPosition(float x, float y) override;
    void center(float windowWidth, float windowHeight, float yOffset) override;

private:
    sf::RectangleShape button;
    sf::Text text;
    bool clicked = false;
    bool released = false;
};

#endif // BUTTON_H
