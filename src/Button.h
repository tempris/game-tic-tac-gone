#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font& font, const std::string& text) {
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
        this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        this->text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void update(const sf::Vector2i& mousePos, sf::Event& event) {
        if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            button.setFillColor(sf::Color(200, 200, 200)); // Hover color
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                button.setFillColor(sf::Color(150, 150, 150)); // Clicked color
                clicked = true;
            }
        }
        else {
            button.setFillColor(sf::Color::White);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool isClicked() {
        if (clicked) {
            clicked = false;
            return true;
        }
        return false;
    }

    float getWidth() const {
        return button.getSize().x;
    }

    float getHeight() const {
        return button.getSize().y;
    }

    void setPosition(float x, float y) {
        button.setPosition(x, y);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setPosition(x + button.getSize().x / 2.0f, y + button.getSize().y / 2.0f);
    }

private:
    sf::RectangleShape button;
    sf::Text text;
    bool clicked = false;
};

#endif // BUTTON_H
