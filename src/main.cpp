#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

enum class GameState {
    MainMenu,
    Playing,
    Paused
};

void handleMainMenu(sf::RenderWindow& window, Button& startButton, Button& quitButton, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        startButton.update(sf::Mouse::getPosition(window), event);
        quitButton.update(sf::Mouse::getPosition(window), event);

        if (startButton.isClicked()) {
            state = GameState::Playing;
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

void handlePlayingState(sf::RenderWindow& window, GameState& state) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            state = GameState::Paused;
        }
    }

    window.clear();
    // Placeholder for game grid drawing
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
            handlePlayingState(window, state);
            break;
        case GameState::Paused:
            handlePauseMenu(window, resumeButton, mainMenuButton, state);
            break;
        }
    }

    return 0;
}
