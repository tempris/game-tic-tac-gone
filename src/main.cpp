#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Window.h"

int main() {
    Window window("Tic-Tac-Toe-Bananza", 800, 600);

    // Initialize the ResourceManager to load the font
    ResourceManager::getInstance();

    GameStateManager gameStateManager(window.getRenderWindow(), window.getRenderWindow().getView());

    window.onResize([&gameStateManager]() {
        gameStateManager.initializeElements();
        });

    window.onEvent([&gameStateManager](const sf::Event& event) {
        gameStateManager.handleEvent(event);
        });

    while (window.isOpen()) {
        window.handleEvents();
        window.clear();
        gameStateManager.draw();
        window.display();
    }

    return 0;
}
