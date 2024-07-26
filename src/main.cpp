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

void initializeGrid();
void drawGrid(sf::RenderWindow& window, sf::Font& font);
bool handleClick(int x, int y);
void handleMainMenu(sf::RenderWindow& window, Button& startButton, Button& quitButton, GameState& state);
void handlePauseMenu(sf::RenderWindow& window, Button& resumeButton, Button& mainMenuButton, GameState& state);
void handlePlayingState(sf::RenderWindow& window, sf::Font& font, GameState& state);
void handleGameOverState(sf::RenderWindow& window, sf::Font& font, Button& mainMenuButton, GameState& state);

void initializeGrid() {
    grid = Grid();
    currentPlayer = PlayerType::Player1;
    winner = PlayerType::None;
}

void drawGrid(sf::RenderWindow& window, sf::Font& font) {
    const float gridStartX = 100.0f;
    const float gridStartY = 100.0f;
    const float cellSize = 100.0f;
    const float gridSizeInPixels = cellSize * gridSize;

    // Center the grid
    const float offsetX = (window.getSize().x - gridSizeInPixels) / 2;
    const float offsetY = (window.getSize().y - gridSizeInPixels) / 2;

    sf::RectangleShape line(sf::Vector2f(gridSizeInPixels, 5));
    line.setFillColor(sf::Color::White);
    for (int i = 1; i < gridSize; ++i) {
        line.setPosition(offsetX, offsetY + i * cellSize);
        window.draw(line);
        line.setSize(sf::Vector2f(5, gridSizeInPixels));
        line.setPosition(offsetX + i * cellSize, offsetY);
        window.draw(line);
        line.setSize(sf::Vector2f(gridSizeInPixels, 5));
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(80);
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            PlayerType cell = grid.getCell(i, j);
            if (cell != PlayerType::None) {
                text.setString(cell == PlayerType::Player1 ? "X" : "O");
                text.setPosition(offsetX + j * cellSize + 20, offsetY + i * cellSize);
                window.draw(text);
            }
        }
    }
}

bool handleClick(int x, int y) {
    const float gridStartX = 100.0f;
    const float gridStartY = 100.0f;
    const float cellSize = 100.0f;
    const float gridSizeInPixels = cellSize * gridSize;

    const float offsetX = (800 - gridSizeInPixels) / 2.0f;
    const float offsetY = (600 - gridSizeInPixels) / 2.0f;

    int row = static_cast<int>((y - offsetY) / cellSize);
    int col = static_cast<int>((x - offsetX) / cellSize);
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize && grid.isCellEmpty(row, col)) {
        grid.setCell(row, col, currentPlayer);
        currentPlayer = (currentPlayer == PlayerType::Player1) ? PlayerType::Player2 : PlayerType::Player1;
        return true;
    }
    return false;
}

void handleMainMenu(sf::RenderWindow& window, Button& startButton, Button& quitButton, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        startButton.update(sf::Mouse::getPosition(window), event);
        quitButton.update(sf::Mouse::getPosition(window), event);

        if (startButton.isClicked()) {
            state = GameState::Playing;
            initializeGrid();
        }

        if (quitButton.isClicked()) {
            window.close();
        }
    }

    window.clear();
    startButton.draw(window);
    quitButton.draw(window);
    window.display();
}

void handlePauseMenu(sf::RenderWindow& window, Button& resumeButton, Button& mainMenuButton, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

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

void handlePlayingState(sf::RenderWindow& window, sf::Font& font, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            state = GameState::Paused;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (currentPlayer == PlayerType::Player1) {
                if (handleClick(event.mouseButton.x, event.mouseButton.y)) {
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
    drawGrid(window, font);
    window.display();
}

void handleGameOverState(sf::RenderWindow& window, sf::Font& font, Button& mainMenuButton, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

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
    winText.setPosition(200, 100);
    window.draw(winText);

    mainMenuButton.draw(window);

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe-Bananza");

    sf::Font font;
    if (!font.loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }

    Button startButton(300, 200, 200, 50, font, "Start Game");
    Button quitButton(300, 300, 200, 50, font, "Quit");
    Button resumeButton(300, 200, 200, 50, font, "Resume");
    Button mainMenuButton(300, 300, 200, 50, font, "Main Menu");

    GameState state = GameState::MainMenu;

    while (window.isOpen()) {
        switch (state) {
        case GameState::MainMenu:
            handleMainMenu(window, startButton, quitButton, state);
            break;
        case GameState::Playing:
            handlePlayingState(window, font, state);
            break;
        case GameState::Paused:
            handlePauseMenu(window, resumeButton, mainMenuButton, state);
            break;
        case GameState::GameOver:
            handleGameOverState(window, font, mainMenuButton, state);
            break;
        }
    }

    return 0;
}
