#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "Button.h"  // Assuming you save the Button class in a file named Button.h

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe-Bananza");

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }

    // Create a text
    sf::Text text("Tic-Tac-Toe", font, 50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(200, 10);

    // Create buttons
    Button closeButton(300, 300, 200, 50, font, "Close");
    Button dummyButton(300, 400, 200, 50, font, "Do Nothing");

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Update button states
            closeButton.update(sf::Mouse::getPosition(window), event);
            dummyButton.update(sf::Mouse::getPosition(window), event);
        }

        // Handle button actions
        if (closeButton.isClicked()) {
            window.close();
        }

        // Clear screen
        window.clear();

        // Draw the text and buttons
        window.draw(text);
        closeButton.draw(window);
        dummyButton.draw(window);

        // Update the window
        window.display();
    }

    return 0;
}
