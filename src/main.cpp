#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Resource.h"
#include "Window.h"
#include "Grid.h"
#include "AI.h"
#include <iostream>

int main() {
    try {
        Window window("Tic-Tac-Gone!", 800, 600);

        // Initialize the Resource to load the font
        Resource& resource = Resource::getInstance();

        // Create the grid and AI instances
        std::unique_ptr<IGrid> grid = std::make_unique<Grid>();
        std::unique_ptr<IAI> ai = std::make_unique<AI>(PlayerType::Player2, PlayerType::Player1);

        // Pass these instances to the Game constructor
        Game game(window.getRenderWindow(), window.getRenderWindow().getView(), std::move(grid), std::move(ai), resource);

        window.onResize([&game]() {
            game.resizeElements();
            });

        window.onEvent([&game](const sf::Event& event) {
            game.handleEvent(event);
            });

        while (window.isOpen()) {
            window.handleEvents();
            game.updateGameLogic();
            window.clear();
            game.draw();
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
