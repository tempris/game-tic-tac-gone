#include "UI.h"
#include "Button.h"
#include "Resource.h"
#include <iostream>

UI::UI(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    startButton(std::make_unique<Button>(0, 0, 200, 50, font, "Start Game")),
    quitButton(std::make_unique<Button>(0, 0, 200, 50, font, "Quit")),
    doNothingButton(std::make_unique<Button>(0, 0, 200, 50, font, "Do Nothing")),
    resumeButton(std::make_unique<Button>(0, 0, 200, 50, font, "Resume")),
    mainMenuButton(std::make_unique<Button>(0, 0, 200, 50, font, "Main Menu")) {
}

void UI::initializeElements() { // TODO: Separate like done in Game
    try {
        startButton->center(window.getSize().x, window.getSize().y, -100);
        quitButton->center(window.getSize().x, window.getSize().y, 0);
        doNothingButton->center(window.getSize().x, window.getSize().y, 100);
        resumeButton->center(window.getSize().x, window.getSize().y, -50);
        mainMenuButton->center(window.getSize().x, window.getSize().y, 50);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
}

void UI::handleMainMenu(const sf::Event& event) {
    try {
        startButton->update(sf::Mouse::getPosition(window), event);
        quitButton->update(sf::Mouse::getPosition(window), event);
        doNothingButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling main menu event: " << e.what() << std::endl;
    }
}

void UI::handlePauseMenu(const sf::Event& event) {
    try {
        resumeButton->update(sf::Mouse::getPosition(window), event);
        mainMenuButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling pause menu event: " << e.what() << std::endl;
    }
}

void UI::handleGameOverState(const sf::Event& event) {
    try {
        mainMenuButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling game over state event: " << e.what() << std::endl;
    }
}

void UI::drawMainMenu() {
    startButton->draw(window);
    quitButton->draw(window);
    doNothingButton->draw(window);
}

void UI::drawPauseMenu() {
    resumeButton->draw(window);
    mainMenuButton->draw(window);
}

void UI::drawGameOverState(PlayerType winner) {
    sf::Text winText;
    winText.setFont(Resource::getInstance().getFont());
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    if (winner == PlayerType::None) {
        winText.setString("Tie Game!");
    }
    else {
        winText.setString(winner == PlayerType::Player1 ? "Player 1 Wins!" : "Player 2 Wins!");
    }
    winText.setPosition((window.getSize().x - winText.getLocalBounds().width) * 0.5f, window.getSize().y * 0.5f - 100.0f);
    window.draw(winText);
    mainMenuButton->draw(window);
}

bool UI::isStartButtonClicked() {
    return startButton->isClicked();
}

bool UI::isQuitButtonClicked() {
    return quitButton->isClicked();
}

bool UI::isDoNothingButtonClicked() {
    return doNothingButton->isClicked();
}

bool UI::isResumeButtonClicked() {
    return resumeButton->isClicked();
}

bool UI::isMainMenuButtonClicked() {
    return mainMenuButton->isClicked();
}
