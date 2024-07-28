#include "Game.h"
#include "Resource.h"

Game::Game(sf::RenderWindow& window, const sf::View& view)
    : window(window), view(view), ai(PlayerType::Player2, PlayerType::Player1),
    ui(window, Resource::getInstance().getFont()),
    state(GameState::MainMenu)
{
    currentPlayer = PlayerType::Player1;
    winner = PlayerType::None;
    initializeElements();
}

void Game::initializeElements() {
    grid.updateSize(window.getSize().x, window.getSize().y);
    ui.initializeElements();
}

void Game::handleMainMenu(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    ui.handleMainMenu(event);

    if (ui.isStartButtonClicked()) {
        grid.initialize();
        currentPlayer = PlayerType::Player1;
        winner = PlayerType::None;
        state = GameState::Playing;
    }

    if (ui.isQuitButtonClicked()) {
        window.close();
    }

    if (ui.isDoNothingButtonClicked()) {
        // Do nothing
    }
}

void Game::handlePauseMenu(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    ui.handlePauseMenu(event);

    if (ui.isResumeButtonClicked()) {
        state = GameState::Playing;
    }

    if (ui.isMainMenuButtonClicked()) {
        state = GameState::MainMenu;
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
        if (currentPlayer == PlayerType::Player1) {
            if (grid.handleClick(event.mouseButton.x, event.mouseButton.y, currentPlayer)) {
                if (grid.checkWin(PlayerType::Player1)) {
                    winner = PlayerType::Player1;
                    state = GameState::GameOver;
                }
                else if (grid.isFull()) {
                    winner = PlayerType::None;
                    state = GameState::GameOver;
                }
                else {
                    currentPlayer = PlayerType::Player2;
                }
            }
        }
    }

    if (currentPlayer == PlayerType::Player2) {
        ai.makeMove(grid);
        if (grid.checkWin(PlayerType::Player2)) {
            winner = PlayerType::Player2;
            state = GameState::GameOver;
        }
        else if (grid.isFull()) {
            winner = PlayerType::None;
            state = GameState::GameOver;
        }
        currentPlayer = PlayerType::Player1;
    }
}

void Game::handleGameOverState(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    ui.handleGameOverState(event);

    if (ui.isMainMenuButtonClicked()) {
        state = GameState::MainMenu;
    }
}

void Game::tick() {
    // No event polling here, handled by Window
}

void Game::draw() {
    switch (state) {
    case GameState::MainMenu:
        ui.drawMainMenu();
        break;
    case GameState::Playing:
        grid.draw(window, Resource::getInstance().getFont());
        break;
    case GameState::Paused:
        ui.drawPauseMenu();
        break;
    case GameState::GameOver:
        ui.drawGameOverState(winner);
        break;
    }
}

void Game::handleEvent(const sf::Event& event) {
    switch (state) {
    case GameState::MainMenu:
        handleMainMenu(event);
        break;
    case GameState::Playing:
        handlePlayingState(event);
        break;
    case GameState::Paused:
        handlePauseMenu(event);
        break;
    case GameState::GameOver:
        handleGameOverState(event);
        break;
    }
}

Game::GameState Game::getState() const {
    return state;
}
