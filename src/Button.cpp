#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font& font, const std::string& text) {
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color::White);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::Black);

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::Black);

    // Adjust the text position to center it within the button
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top + textRect.height * 0.5f);
    this->text.setPosition(x + width * 0.5f, y + height * 0.5f);
}

void Button::update(const sf::Vector2i& mousePos, const sf::Event& event) {
    bool isMouseOver = button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver) {
            button.setFillColor(sf::Color(150, 150, 150)); // Clicked color
            clicked = true;
            released = false;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver && clicked) {
            released = true; // Only allow released if the button is hovered
        }
        clicked = false;
    }

    if (clicked && isMouseOver) {
        button.setFillColor(sf::Color(150, 150, 150)); // Clicked color
    }
    else if (isMouseOver && !released) {
        button.setFillColor(sf::Color(200, 200, 200)); // Hover color
    }
    else {
        button.setFillColor(sf::Color::White); // Default color
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isReleased() {
    if (released) {
        released = false;
        return true;
    }
    return false;
}

float Button::getWidth() const {
    return button.getSize().x;
}

float Button::getHeight() const {
    return button.getSize().y;
}

void Button::setPosition(float x, float y) {
    button.setPosition(x, y);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setPosition(x + button.getSize().x * 0.5f, y + button.getSize().y * 0.5f);
}

void Button::center(float windowWidth, float windowHeight, float yOffset) {
    setPosition((windowWidth - getWidth()) * 0.5f, (windowHeight - getHeight()) * 0.5f + yOffset);
}
