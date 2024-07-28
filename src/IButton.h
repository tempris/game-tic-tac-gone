#ifndef IBUTTON_H
#define IBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class IButton {
public:
    virtual ~IButton() = default;
    virtual void update(const sf::Vector2i& mousePos, const sf::Event& event) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isClicked() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void center(float windowWidth, float windowHeight, float yOffset) = 0;
};

#endif // IBUTTON_H
