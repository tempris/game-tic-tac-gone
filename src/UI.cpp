#include <iostream>
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Button.h"
#include "Resource.h"

UI::UI(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    startButton(std::make_unique<Button>(0, 0, 225, 50, font, "Start Game")),
    startClassicButton(std::make_unique<Button>(0, 0, 225, 50, font, "Classic Game")),
    quitButton(std::make_unique<Button>(0, 0, 225, 50, font, "Quit")),
    resumeButton(std::make_unique<Button>(0, 0, 225, 50, font, "Resume")),
    mainMenuPauseButton(std::make_unique<Button>(0, 0, 225, 50, font, "Main Menu")),
    mainMenuGameOverButton(std::make_unique<Button>(0, 0, 225, 50, font, "Main Menu")),
    mainMenuGameOverTieButton(std::make_unique<Button>(0, 0, 225, 50, font, "Main Menu")) {
}

void UI::initializeElementsMainMenu() {
    try {
        startButton->center(window, 25);
        startClassicButton->center(window, 100);
        quitButton->center(window, 175);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
}

void UI::initializeElementsPauseMenu() {
    try {
        resumeButton->center(window, -50);
        mainMenuPauseButton->center(window, 50);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
}

void UI::initializeElementsGameOver(float offsetY) {
    try {
        mainMenuGameOverButton->center(window, 125);
        mainMenuGameOverTieButton->center(window, 50);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
}

void UI::initializeElements() {
    initializeElementsMainMenu();
    initializeElementsPauseMenu();
    initializeElementsGameOver();
}

void UI::handleMainMenu(const sf::Event& event) {
    try {
        startButton->update(sf::Mouse::getPosition(window), event);
        startClassicButton->update(sf::Mouse::getPosition(window), event);
        quitButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling main menu event: " << e.what() << std::endl;
    }
}

void UI::handlePauseMenu(const sf::Event& event) {
    try {
        resumeButton->update(sf::Mouse::getPosition(window), event);
        mainMenuPauseButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling pause menu event: " << e.what() << std::endl;
    }
}

void UI::handleGameOverState(const sf::Event& event) {
    try {
        mainMenuGameOverButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling game over state event: " << e.what() << std::endl;
    }
}

void UI::handleGameOverTieState(const sf::Event& event) {
    try {
        mainMenuGameOverTieButton->update(sf::Mouse::getPosition(window), event);
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling game over state event: " << e.what() << std::endl;
    }
}

void UI::drawMainMenu() {
    sf::Sprite sprite;
    sprite.setTexture(Resource::getInstance().getBrandTexture());
    sprite.setScale(sf::Vector2f(0.375f, 0.375f));
    sprite.setPosition((window.getSize().x - sprite.getLocalBounds().width * 0.375f) * 0.5f, window.getSize().y * 0.5f - 200.0f); // Adjust the position as needed
    window.draw(sprite);

    // Draw buttons
    startButton->draw(window);
    startClassicButton->draw(window);
    quitButton->draw(window);
}

void UI::drawPauseMenu() {
    resumeButton->draw(window);
    mainMenuPauseButton->draw(window);
}

void UI::drawGameOverState(PlayerType winner) {
    // Create the background panel
    sf::RectangleShape backgroundPanel;

    backgroundPanel.setFillColor(sf::Color(0, 0, 0, 220));

    backgroundPanel.setSize(sf::Vector2f(250.0f, winner == PlayerType::None ? 225.0f : 350.0f));
    backgroundPanel.setPosition((window.getSize().x * 0.5f - backgroundPanel.getSize().x * 0.5f), window.getSize().y * 0.5f - backgroundPanel.getSize().y * 0.5f);

    // Draw the background panel
    window.draw(backgroundPanel);

    sf::Sprite winSprite;

    if (winner == PlayerType::None) {
        winSprite.setTexture(Resource::getInstance().getTieTexture());
    }
    else if (winner == PlayerType::Player1) {
        winSprite.setColor(sf::Color(255, 30, 38));
        winSprite.setTexture(Resource::getInstance().getWinTexture());
    }
    else {
        winSprite.setColor(sf::Color(22, 200, 255));
        winSprite.setTexture(Resource::getInstance().getWinTexture());
    }

    winSprite.setScale(sf::Vector2f(0.375f, 0.375f));
    winSprite.setPosition((window.getSize().x - winSprite.getLocalBounds().width * 0.375f) * 0.5f, window.getSize().y * 0.5f + (winner == PlayerType::None ? -75.0f : 0.0f));

    window.draw(winSprite);

    if (winner != PlayerType::None) {
        sf::Sprite playerSprite;

        if (winner == PlayerType::Player1) {
            winSprite.setColor(sf::Color(255, 30, 38));
            winSprite.setTexture(Resource::getInstance().getWinTexture());
            playerSprite.setTexture(Resource::getInstance().getXTexture());
        }
        else {
            winSprite.setColor(sf::Color(22, 200, 255));
            winSprite.setTexture(Resource::getInstance().getWinTexture());
            playerSprite.setTexture(Resource::getInstance().getOTexture());
        }

        playerSprite.setScale(sf::Vector2f(0.25f, 0.25f));
        playerSprite.setPosition((window.getSize().x - playerSprite.getLocalBounds().width * 0.25f) * 0.5f, window.getSize().y * 0.5f - 150.0f);

        window.draw(playerSprite);

        mainMenuGameOverButton->draw(window);
    }
    else {
        mainMenuGameOverTieButton->draw(window);
    }

}

bool UI::isStartButtonReleased() {
    return startButton->isReleased();
}

bool UI::isStartClassicButtonReleased() {
    return startClassicButton->isReleased();
}

bool UI::isQuitButtonReleased() {
    return quitButton->isReleased();
}

bool UI::isResumeButtonReleased() {
    return resumeButton->isReleased();
}

bool UI::isMainMenuButtonReleased() {
    return mainMenuPauseButton->isReleased() || mainMenuGameOverButton->isReleased() || mainMenuGameOverTieButton->isReleased();
}
