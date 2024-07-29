#include <iostream>
#include <random>
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "Resource.h"

static const sf::Time GameOverDelay = sf::seconds(3); // 3 seconds delay

Game::Game(sf::RenderWindow& window, const sf::View& view, std::unique_ptr<IGrid> grid, std::unique_ptr<IAI> ai, IResource& resource)
    : window(window), view(view), grid(std::move(grid)),
    ai(std::move(ai)),
    ui(window, resource.getFont()),
    state(GameState::MainMenu)
{
    currentPlayer = PlayerType::Player1;
    winner = PlayerType::None;
    initializeElements();
}

void Game::resizeElements() {
    grid->updateSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    ui.initializeElements();
}

void Game::initializeElements() {
    grid->initialize();
    resizeElements();
}

void Game::handleEvent(const sf::Event& event) {
    try {
        if (state == GameState::MainMenu) {
            ui.handleMainMenu(event);
            if (ui.isStartButtonReleased()) {
                state = GameState::Playing;
                grid->initialize();
            }
            if (ui.isQuitButtonReleased()) {
                window.close();
            }
        }
        else if (state == GameState::Paused) {
            ui.handlePauseMenu(event);
            if (ui.isResumeButtonReleased()) {
                state = GameState::Playing;
            }
            if (ui.isMainMenuButtonReleased()) {
                state = GameState::MainMenu;
            }
        }
        else if (state == GameState::Playing) {
            handlePlayingState(event);
        }
        else if (state == GameState::GameOver) {
            ui.handleGameOverState(event);
            if (ui.isMainMenuButtonReleased()) {
                state = GameState::MainMenu;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling event: " << e.what() << std::endl;
    }
}

void Game::handlePlayingState(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Paused;
    }

    if (currentPlayer == PlayerType::Player1 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        try {
            if (currentPlayer == PlayerType::Player1) {
                if (grid->handleClick(event.mouseButton.x, event.mouseButton.y, currentPlayer)) {
                    if (grid->checkWin(PlayerType::Player1)) {
                        winner = PlayerType::Player1;
                        state = GameState::GameOver;
                    }
                    else if (grid->isFull()) {
                        winner = PlayerType::None;
                        state = GameState::GameOver;
                    }
                    else {
                        currentPlayer = PlayerType::Player2;
                    }
                }
            }

            if (currentPlayer == PlayerType::Player2) {
                triggerAIMove();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during game play: " << e.what() << std::endl;
        }
    }
}

void Game::triggerAIMove() {
    int totalCells = gridSize * gridSize;
    int emptyCells = grid->countEmptyCells();
    float proportionOfEmptyCells = static_cast<float>(emptyCells) / totalCells;

    aiMoveDelayDuration = 0.2f + proportionOfEmptyCells + (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (1.0f - proportionOfEmptyCells));

    std::cout << "aiMoveDelayDuration: " << aiMoveDelayDuration << std::endl;

    aiMoveDelayClock.restart();  // Start the clock
    aiMoveScheduled = true;
}

void Game::updateGameLogic() {
    if (aiMoveScheduled && aiMoveDelayClock.getElapsedTime() >= sf::seconds(aiMoveDelayDuration)) {
        ai->makeMove(*grid);  // Execute AI move

        if (grid->checkWin(PlayerType::Player2)) {
            winner = PlayerType::Player2;
            state = GameState::GameOver;
        }
        else if (grid->isFull()) {
            winner = PlayerType::None;
            state = GameState::GameOver;
        }

        currentPlayer = PlayerType::Player1;

        aiMoveScheduled = false;  // Reset the schedule flag
    }
}

void Game::draw() {
    if (state == GameState::MainMenu) {
        ui.drawMainMenu();
    }
    else if (state == GameState::Paused) {
        ui.drawPauseMenu();
    }
    else if (state == GameState::Playing) {
        grid->draw(window, !aiMoveScheduled);
    }
    else if (state == GameState::GameOver) {
        grid->draw(window, false);  // Keep drawing the grid for a few seconds
        ui.drawGameOverState(winner);
    }
}

Game::GameState Game::getState() const {
    return state;
}
