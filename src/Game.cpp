#include "Game.h"
#include "Resource.h"
#include <iostream>

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
            if (ui.isStartButtonClicked()) {
                state = GameState::Playing;
                grid->initialize();
            }
            if (ui.isQuitButtonClicked()) {
                window.close();
            }
        }
        else if (state == GameState::Paused) {
            ui.handlePauseMenu(event);
            if (ui.isResumeButtonClicked()) {
                state = GameState::Playing;
            }
            if (ui.isMainMenuButtonClicked()) {
                state = GameState::MainMenu;
            }
        }
        else if (state == GameState::Playing) {
            handlePlayingState(event);
        }
        else if (state == GameState::GameOver) {
            ui.handleGameOverState(event);
            if (ui.isMainMenuButtonClicked()) {
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

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
                ai->makeMove(*grid);
                if (grid->checkWin(PlayerType::Player2)) {
                    winner = PlayerType::Player2;
                    state = GameState::GameOver;
                }
                else if (grid->isFull()) {
                    winner = PlayerType::None;
                    state = GameState::GameOver;
                }
                currentPlayer = PlayerType::Player1;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during game play: " << e.what() << std::endl;
        }
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
        grid->draw(window, Resource::getInstance().getFont());
    }
    else if (state == GameState::GameOver) {
        ui.drawGameOverState(winner);
    }
}

Game::GameState Game::getState() const {
    return state;
}
