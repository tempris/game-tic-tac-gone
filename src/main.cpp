#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameStateManager.h"
#include "ResourceManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe-Bananza");
    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    // Initialize the ResourceManager to load the font
    ResourceManager::getInstance();

    GameStateManager gameStateManager(window, view);

    while (window.isOpen()) {
        gameStateManager.tick();
    }

    return 0;
}
