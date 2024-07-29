#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "IButton.h"
#include "Shared.h"

class UI {
public:
    UI(sf::RenderWindow& window, sf::Font& font);

    void initializeElementsMainMenu();
    void initializeElementsPauseMenu();
    void initializeElementsGameOver(float offsetY = 0.0f);
    void initializeElements();
    void handleMainMenu(const sf::Event& event);
    void handlePauseMenu(const sf::Event& event);
    void handleGameOverState(const sf::Event& event);
    void handleGameOverTieState(const sf::Event& event);
    void drawMainMenu();
    void drawPauseMenu();
    void drawGameOverState(PlayerType winner);

    bool isStartButtonReleased();
    bool isStartClassicButtonReleased();
    bool isQuitButtonReleased();
    bool isResumeButtonReleased();
    bool isMainMenuButtonReleased();

private:
    sf::RenderWindow& window;

    std::unique_ptr<IButton> startButton;
    std::unique_ptr<IButton> startClassicButton;
    std::unique_ptr<IButton> quitButton;
    std::unique_ptr<IButton> resumeButton;
    std::unique_ptr<IButton> mainMenuPauseButton;
    std::unique_ptr<IButton> mainMenuGameOverButton;
    std::unique_ptr<IButton> mainMenuGameOverTieButton;
};

#endif // UI_H
