#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "Grid.h"
#include "Player.h"
#include "AI.h"
#include "GameDefinitions.h"

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver
};

Grid grid;
PlayerType currentPlayer = PlayerType::Player1;
PlayerType winner = PlayerType::None;

AI ai(PlayerType::Player2, PlayerType::Player1);

// Declare buttons globally without initialization
Button startButton(0, 0, 200, 50, *(new sf::Font()), "Start Game");
Button quitButton(0, 0, 200, 50, *(new sf::Font()), "Quit");
Button doNothingButton(0, 0, 200, 50, *(new sf::Font()), "Do Nothing");
Button resumeButton(0, 0, 200, 50, *(new sf::Font()), "Resume");
Button mainMenuButton(0, 0, 200, 50, *(new sf::Font()), "Main Menu");

void centerButton(Button& button, float windowWidth, float windowHeight, float yOffset);
void handleMainMenu(sf::RenderWindow& window, GameState& state, sf::View& view);
void handlePauseMenu(sf::RenderWindow& window, GameState& state, sf::View& view);
void handlePlayingState(sf::RenderWindow& window, sf::Font& font, GameState& state, sf::View& view);
void handleGameOverState(sf::RenderWindow& window, sf::Font& font, GameState& state, sf::View& view);
void updateView(sf::RenderWindow& window, sf::View& view);
void initializeElements(sf::RenderWindow& window, sf::View& view);

void centerButton(Button& button, float windowWidth, float windowHeight, float yOffset) {
    float buttonWidth = button.getWidth();
    float buttonHeight = button.getHeight();
    button.setPosition((windowWidth - buttonWidth) / 2.0f, (windowHeight - buttonHeight) / 2.0f + yOffset);
}

void updateView(sf::RenderWindow& window, sf::View& view) {
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    window.setView(view);
}

void initializeElements(sf::RenderWindow& window, sf::View& view) {
    updateView(window, view);
    grid.updateSize(window.getSize().x, window.getSize().y);
    centerButton(startButton, window.getSize().x, window.getSize().y, -100);
    centerButton(quitButton, window.getSize().x, window.getSize().y, 0);
    centerButton(doNothingButton, window.getSize().x, window.getSize().y, 100);
    centerButton(resumeButton, window.getSize().x, window.getSize().y, -50);
    centerButton(mainMenuButton, window.getSize().x, window.getSize().y, 50);
}

void handleMainMenu(sf::RenderWindow& window, GameState& state, sf::View& view) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized) {
            initializeElements(window, view);
        }

        startButton.update(sf::Mouse::getPosition(window), event);
        quitButton.update(sf::Mouse::getPosition(window), event);
        doNothingButton.update(sf::Mouse::getPosition(window), event);

        if (startButton.isClicked()) {
            state = GameState::Playing;
            grid.initialize();
            currentPlayer = PlayerType::Player1;
            winner = PlayerType::None;
        }

        if (quitButton.isClicked()) {
            window.close();
        }

        if (doNothingButton.isClicked()) {
            // Do nothing
        }
    }

    window.clear();
    startButton.draw(window);
    quitButton.draw(window);
    doNothingButton.draw(window);
    window.display();
}

void handlePauseMenu(sf::RenderWindow& window, GameState& state, sf::View& view) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized) {
            initializeElements(window, view);
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

    window.clear();
    resumeButton.draw(window);
    mainMenuButton.draw(window);
    window.display();
}

void handlePlayingState(sf::RenderWindow& window, sf::Font& font, GameState& state, sf::View& view) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized) {
            initializeElements(window, view);
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

    window.clear();
    grid.draw(window, font);
    window.display();
}

void handleGameOverState(sf::RenderWindow& window, sf::Font& font, GameState& state, sf::View& view) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized) {
            initializeElements(window, view);
        }

        mainMenuButton.update(sf::Mouse::getPosition(window), event);

        if (mainMenuButton.isClicked()) {
            state = GameState::MainMenu;
        }
    }

    window.clear();

    sf::Text winText;
    winText.setFont(font);
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

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe-Bananza");

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    sf::Font font;
    if (!font.loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }

    // Initialize button text with font after loading the font
    startButton = Button(300, 200, 200, 50, font, "Start Game");
    quitButton = Button(300, 300, 200, 50, font, "Quit");
    doNothingButton = Button(300, 400, 200, 50, font, "Do Nothing");
    resumeButton = Button(300, 200, 200, 50, font, "Resume");
    mainMenuButton = Button(300, 300, 200, 50, font, "Main Menu");

    // Initialize elements initially
    initializeElements(window, view);

    GameState state = GameState::MainMenu;

    while (window.isOpen()) {
        switch (state) {
        case GameState::MainMenu:
            handleMainMenu(window, state, view);
            break;
        case GameState::Playing:
            handlePlayingState(window, font, state, view);
            break;
        case GameState::Paused:
            handlePauseMenu(window, state, view);
            break;
        case GameState::GameOver:
            handleGameOverState(window, font, state, view);
            break;
        }
    }

    return 0;
}
