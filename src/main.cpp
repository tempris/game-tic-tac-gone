#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "Window.h"

int main() {
    Window window("Tic-Tac-Toe-Bananza", 800, 600);

    // Initialize the ResourceManager to load the font
    ResourceManager::getInstance();

    Game game(window.getRenderWindow(), window.getRenderWindow().getView());

    window.onResize([&game]() {
        game.initializeElements();
        });

    window.onEvent([&game](const sf::Event& event) {
        game.handleEvent(event);
        });

    while (window.isOpen()) {
        window.handleEvents();
        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}
