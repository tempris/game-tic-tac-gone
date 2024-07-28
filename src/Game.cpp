#include "Game.h"
#include "ResourceManager.h"

Game::Game(sf::RenderWindow& window, const sf::View& view)
    : window(window), view(view), ai(PlayerType::Player2, PlayerType::Player1),
    startButton(0, 0, 200, 50, ResourceManager::getInstance().getFont(), "Start Game"),
    quitButton(0, 0, 200, 50, ResourceManager::getInstance().getFont(), "Quit"),
    doNothingButton(0, 0, 200, 50, ResourceManager::getInstance().getFont(), "Do Nothing"),
    resumeButton(0, 0, 200, 50, ResourceManager::getInstance().getFont(), "Resume"),
    mainMenuButton(0, 0, 200, 50, ResourceManager::getInstance().getFont(), "Main Menu"),
    state(GameState::MainMenu)
{
    currentPlayer = PlayerType::Player1;
    winner = PlayerType::None;
    initializeElements();
}

void Game::initializeElements() {
    grid.updateSize(window.getSize().x, window.getSize().y);
    startButton.center(window.getSize().x, window.getSize().y, -100);
    quitButton.center(window.getSize().x, window.getSize().y, 0);
    doNothingButton.center(window.getSize().x, window.getSize().y, 100);
    resumeButton.center(window.getSize().x, window.getSize().y, -50);
    mainMenuButton.center(window.getSize().x, window.getSize().y, 50);
}

void Game::handleMainMenu(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    startButton.update(sf::Mouse::getPosition(window), event);
    quitButton.update(sf::Mouse::getPosition(window), event);
    doNothingButton.update(sf::Mouse::getPosition(window), event);

    if (startButton.isClicked()) {
        grid.initialize();
        currentPlayer = PlayerType::Player1;
        winner = PlayerType::None;
        state = GameState::Playing;
    }

    if (quitButton.isClicked()) {
        window.close();
    }

    if (doNothingButton.isClicked()) {
        // Do nothing
    }
}

void Game::handlePauseMenu(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    resumeButton.update(sf::Mouse::getPosition(window), event);
    mainMenuButton.update(sf::Mouse::getPosition(window), event);

    if (resumeButton.isClicked()) {
        state = GameState::Playing;
    }

    if (mainMenuButton.isClicked()) {
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

    mainMenuButton.update(sf::Mouse::getPosition(window), event);

    if (mainMenuButton.isClicked()) {
        state = GameState::MainMenu;
    }
}

void Game::tick() {
    // No event polling here, handled by Window
}

void Game::draw() {
    switch (state) {
    case GameState::MainMenu:
        startButton.draw(window);
        quitButton.draw(window);
        doNothingButton.draw(window);
        break;
    case GameState::Playing:
        grid.draw(window, ResourceManager::getInstance().getFont());
        break;
    case GameState::Paused:
        resumeButton.draw(window);
        mainMenuButton.draw(window);
        break;
    case GameState::GameOver:
        sf::Text winText;
        winText.setFont(ResourceManager::getInstance().getFont());
        winText.setCharacterSize(50);
        winText.setFillColor(sf::Color::White);
        if (winner == PlayerType::None) {
            winText.setString("Tie Game!");
        }
        else {
            winText.setString(winner == PlayerType::Player1 ? "Player 1 Wins!" : "Player 2 Wins!");
        }
        winText.setPosition((window.getSize().x - winText.getLocalBounds().width) / 2.0f, 100);
        window.draw(winText);
        mainMenuButton.draw(window);
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
