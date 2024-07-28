#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Shared.h"

class UI {
public:
    UI(sf::RenderWindow& window, sf::Font& font);

    void initializeElements();
    void handleMainMenu(const sf::Event& event);
    void handlePauseMenu(const sf::Event& event);
    void handleGameOverState(const sf::Event& event);
    void drawMainMenu();
    void drawPauseMenu();
    void drawGameOverState(PlayerType winner);

    bool isStartButtonClicked();
    bool isQuitButtonClicked();
    bool isDoNothingButtonClicked();
    bool isResumeButtonClicked();
    bool isMainMenuButtonClicked();

private:
    sf::RenderWindow& window;

    Button startButton;
    Button quitButton;
    Button doNothingButton;
    Button resumeButton;
    Button mainMenuButton;
};

#endif // UI_H
