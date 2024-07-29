#include <iostream>
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Button.h"
#include "Resource.h"

UI::UI(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    startButton(std::make_unique<Button>(0, 0, 200, 50, font, "Start Game")),
    quitButton(std::make_unique<Button>(0, 0, 200, 50, font, "Quit")),
    resumeButton(std::make_unique<Button>(0, 0, 200, 50, font, "Resume")),
    mainMenuButton(std::make_unique<Button>(0, 0, 200, 50, font, "Main Menu")) {
}

void UI::initializeElements() {
    try {
        startButton->center(window.getSize().x, window.getSize().y, 50);
        quitButton->center(window.getSize().x, window.getSize().y, 150);
        resumeButton->center(window.getSize().x, window.getSize().y, -50);
        mainMenuButton->center(window.getSize().x, window.getSize().y, 125);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize UI elements: " << e.what() << std::endl;
    }
}

void UI::handleMainMenu(const sf::Event& event) {
    try {
        startButton->update(sf::Mouse::getPosition(window), event);
        quitButton->update(sf::Mouse::getPosition(window), event);
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

void UI::drawMainMenuTextLogo() {
    sf::Text text;
    text.setFont(Resource::getInstance().getFont());
    text.setCharacterSize(50);  // Set the character size

    float textRectHeight = 0.0f;

    // Calculate total width
    text.setString("Tic - ");
    sf::FloatRect ticRect = text.getLocalBounds();
    float ticWidth = ticRect.width;
    textRectHeight += ticRect.height;

    text.setString("Tac - ");
    sf::FloatRect tacRect = text.getLocalBounds();
    float tacWidth = tacRect.width;
    textRectHeight += ticRect.height;

    text.setString("Gone!");
    sf::FloatRect goneRect = text.getLocalBounds();
    float goneWidth = goneRect.width;
    textRectHeight += ticRect.height;

    float totalWidth = ticWidth + tacWidth + goneWidth;

    // Calculate starting position to center the text
    float startX = (window.getSize().x - totalWidth) * 0.5f;
    float yPosition = window.getSize().y * 0.5f - 100.0f;  // Y position for all texts

    // Draw "Tic-"
    text.setString("Tic - ");
    text.setFillColor(sf::Color::Red);  // Red color for "Tic"
    text.setOrigin(0, textRectHeight / 2);
    text.setPosition(startX, yPosition);
    window.draw(text);

    // Draw "Tac-"
    text.setString("Tac - ");
    text.setFillColor(sf::Color::Blue);  // Blue color for "Tac"
    text.setOrigin(0, textRectHeight / 2);
    text.setPosition(startX + ticWidth, yPosition);
    window.draw(text);

    // Draw "Gone!"
    text.setString("Gone!");
    text.setFillColor(sf::Color(255, 0, 0, 128));  // Half-transparent red for "Gone"
    text.setOrigin(0, textRectHeight / 2);
    text.setPosition(startX + ticWidth + tacWidth, yPosition);
    window.draw(text);
}

void UI::drawMainMenu() {
    sf::Sprite sprite;
    sprite.setTexture(Resource::getInstance().getBrandTexture());
    sprite.setScale(sf::Vector2f(0.375f, 0.375f));
    sprite.setPosition((window.getSize().x - sprite.getLocalBounds().width * 0.375f) * 0.5f, window.getSize().y * 0.5f - 200.0f); // Adjust the position as needed
    window.draw(sprite);

    // Draw buttons
    startButton->draw(window);
    quitButton->draw(window);
}

void UI::drawPauseMenu() {
    resumeButton->draw(window);
    mainMenuButton->draw(window);
}

void UI::drawGameOverState(PlayerType winner) {
    bool useText = false;

    // Create the background panel
    sf::RectangleShape backgroundPanel;

    backgroundPanel.setFillColor(sf::Color(0, 0, 0, 200));

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
    mainMenuButton->draw(window);

}

bool UI::isStartButtonReleased() {
    return startButton->isReleased();
}

bool UI::isQuitButtonReleased() {
    return quitButton->isReleased();
}

bool UI::isResumeButtonReleased() {
    return resumeButton->isReleased();
}

bool UI::isMainMenuButtonReleased() {
    return mainMenuButton->isReleased();
}
