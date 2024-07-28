#include "Game.h"
#include "Resource.h"
#include "AI.h"
#include "Grid.h"

Game::Game(sf::RenderWindow& window, const sf::View& view, IResource& resource)
    : window(window), view(view), grid(std::make_unique<Grid>()),
    ai(std::make_unique<AI>(PlayerType::Player2, PlayerType::Player1)),
    ui(window, resource.getFont()),
    state(GameState::MainMenu)
{
    currentPlayer = PlayerType::Player1;
    winner = PlayerType::None;
    initializeElements();
}

void Game::initializeElements() {
    grid->updateSize(view.getSize().x, view.getSize().y);
    grid->initialize();
    ui.initializeElements();
}

void Game::handleEvent(const sf::Event& event) {
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

void Game::handlePlayingState(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Paused;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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

void Game::draw() {
    window.setView(view);
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
