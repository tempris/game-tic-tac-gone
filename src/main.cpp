#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver
};

enum class Player {
    None,
    Player1,
    Player2
};

const int gridSize = 3;
Player grid[gridSize][gridSize];
Player currentPlayer = Player::Player1;
Player winner = Player::None;

void initializeGrid() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = Player::None;
        }
    }
    currentPlayer = Player::Player1;
    winner = Player::None;
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
            if (grid[i][j] != Player::None) {
                text.setString(grid[i][j] == Player::Player1 ? "X" : "O");
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

    const float offsetX = (800 - gridSizeInPixels) / 2;
    const float offsetY = (600 - gridSizeInPixels) / 2;

    int row = (y - offsetY) / cellSize;
    int col = (x - offsetX) / cellSize;
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize && grid[row][col] == Player::None) {
        grid[row][col] = currentPlayer;
        currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
        return true;
    }
    return false;
}

bool checkWin(Player player) {
    for (int i = 0; i < gridSize; ++i) {
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
            return true;
        if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
            return true;
    }
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
        return true;
    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
        return true;
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
            if (handleClick(event.mouseButton.x, event.mouseButton.y)) {
                if (checkWin(Player::Player1)) {
                    winner = Player::Player1;
                    state = GameState::GameOver;
                }
                else if (checkWin(Player::Player2)) {
                    winner = Player::Player2;
                    state = GameState::GameOver;
                }
            }
        }
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
    winText.setString(winner == Player::Player1 ? "Player 1 Wins!" : "Player 2 Wins!");
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
