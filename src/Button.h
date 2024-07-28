#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font& font, const std::string& text);

    void update(const sf::Vector2i& mousePos, const sf::Event& event);
    void draw(sf::RenderWindow& window);
    bool isClicked();
    float getWidth() const;
    float getHeight() const;
    void setPosition(float x, float y);
    void center(float windowWidth, float windowHeight, float yOffset);

private:
    sf::RectangleShape button;
    sf::Text text;
    bool clicked = false;
};

#endif // BUTTON_H
