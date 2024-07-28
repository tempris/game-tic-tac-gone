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
    GameStateManager(sf::RenderWindow& window, sf::View& view);

    void handleMainMenu();
    void handlePauseMenu();
    void handlePlayingState();
    void handleGameOverState();
    void initializeElements();
    void tick();

private:
    sf::RenderWindow& window;
    sf::View& view;
    Grid grid;
    PlayerType currentPlayer;
    PlayerType winner;
    AI ai;

    Button startButton;
    Button quitButton;
    Button doNothingButton;
    Button resumeButton;
    Button mainMenuButton;

    enum class GameState {
        MainMenu,
        Playing,
        Paused,
        GameOver
    };

    GameState state;
};

#endif // GAME_STATE_MANAGER_H
