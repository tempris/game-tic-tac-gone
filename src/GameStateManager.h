#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Grid.h"
#include "Player.h"
#include "AI.h"
#include "Shared.h"

class GameStateManager {
public:
    GameStateManager(sf::RenderWindow& window, const sf::View& view);

    void handleMainMenu(const sf::Event& event);
    void handlePauseMenu(const sf::Event& event);
    void handlePlayingState(const sf::Event& event);
    void handleGameOverState(const sf::Event& event);
    void initializeElements();
    void tick();
    void draw();
    void handleEvent(const sf::Event& event);

    enum class GameState {
        MainMenu,
        Playing,
        Paused,
        GameOver
    };

    GameState getState() const;

private:
    sf::RenderWindow& window;
    sf::View view;
    Grid grid;
    PlayerType currentPlayer;
    PlayerType winner;
    AI ai;

    Button startButton;
    Button quitButton;
    Button doNothingButton;
    Button resumeButton;
    Button mainMenuButton;

    GameState state;
};

#endif // GAME_STATE_MANAGER_H
