#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(float x, float y, float width, float height, const sf::Font& font, const std::string& text) {
        buttonShape.setPosition(sf::Vector2f(x, y));
        buttonShape.setSize(sf::Vector2f(width, height));
        buttonShape.setFillColor(defaultColor);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(
            x + (width / 2.f) - (buttonText.getGlobalBounds().width / 2.f),
            y + (height / 2.f) - (buttonText.getGlobalBounds().height / 2.f)
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    void update(const sf::Vector2i& mousePos, sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                isPressed = true;
                buttonShape.setFillColor(clickColor);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (isPressed && buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                isPressed = false;
                buttonShape.setFillColor(hoverColor);
                wasClicked = true;
            }
            else {
                isPressed = false;
                buttonShape.setFillColor(defaultColor);
            }
        }
        else {
            isHovered(mousePos);
        }
    }

    bool isClicked() {
        if (wasClicked) {
            wasClicked = false;
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;

    bool isPressed = false;
    bool wasClicked = false;

    sf::Color defaultColor = sf::Color::Green;
    sf::Color hoverColor = sf::Color::Yellow;
    sf::Color clickColor = sf::Color::Red;

    void isHovered(const sf::Vector2i& mousePos) {
        if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            if (!isPressed)
                buttonShape.setFillColor(hoverColor);
        }
        else {
            if (!isPressed)
                buttonShape.setFillColor(defaultColor);
        }
    }
};

#endif // BUTTON_H
