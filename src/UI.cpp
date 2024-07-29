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
    mainMenuGameOverButton(std::make_unique<Button>(0, 0, 225, 50, font, "Main Menu")) {
}

void UI::initializeElements() {
    try {
        startButton->center(window, 25);
        startClassicButton->center(window, 100);
        quitButton->center(window, 175);
        resumeButton->center(window, -50);
        mainMenuPauseButton->center(window, 50);
        mainMenuGameOverButton->center(window, 125);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
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
    bool useText = false;

    // Create the background panel
    sf::RectangleShape backgroundPanel;

    backgroundPanel.setFillColor(sf::Color(0, 0, 0, 220));

    if (useText) {
        backgroundPanel.setSize(sf::Vector2f(250.0f, 250.0f));
        backgroundPanel.setPosition((window.getSize().x * 0.5f - backgroundPanel.getSize().x * 0.5f), window.getSize().y * 0.5f - backgroundPanel.getSize().y * 0.5f);
    }
    else {
        backgroundPanel.setSize(sf::Vector2f(250.0f, 350.0f));
        backgroundPanel.setPosition((window.getSize().x * 0.5f - backgroundPanel.getSize().x * 0.5f), window.getSize().y * 0.5f - backgroundPanel.getSize().y * 0.5f);
    }

    // Draw the background panel
    window.draw(backgroundPanel);

    if (useText) {
        sf::Text winText;
        winText.setFont(Resource::getInstance().getFont());
        winText.setCharacterSize(50);
        if (winner == PlayerType::None) {
            winText.setString("Tie Game!");
            winText.setFillColor(sf::Color::White);  // White for a tie
        }
        else if (winner == PlayerType::Player1) {
            winText.setString("X Wins!");
            winText.setFillColor(sf::Color::Red);  // Red for Player 1
        }
        else {
            winText.setString("O Wins!");
            winText.setFillColor(sf::Color::Blue);  // Blue for Player 2
        }
        winText.setPosition((window.getSize().x - winText.getLocalBounds().width) * 0.5f, window.getSize().y * 0.5f - 100.0f);
        window.draw(winText);
    }
    else {
        sf::Sprite playerSprite;
        sf::Sprite winSprite;

        if (winner == PlayerType::None) {
            winSprite.setTexture(Resource::getInstance().getTieTexture());
        }
        else if (winner == PlayerType::Player1) {
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

        winSprite.setScale(sf::Vector2f(0.375f, 0.375f));
        winSprite.setPosition((window.getSize().x - winSprite.getLocalBounds().width * 0.375f) * 0.5f, window.getSize().y * 0.5f);

        window.draw(playerSprite);
        window.draw(winSprite);
    }
    mainMenuGameOverButton->draw(window);

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
    return mainMenuPauseButton->isReleased() || mainMenuGameOverButton->isReleased();
}
