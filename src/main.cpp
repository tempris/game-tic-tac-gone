#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Resource.h"
#include "Window.h"
#include "Grid.h"
#include "AI.h"

int main() {
    Window window("Tic-Tac-Toe-Bananza", 800, 600);

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
        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}
