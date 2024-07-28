#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"
#include "IAI.h"
#include "Shared.h"
#include "UI.h"
#include "IResource.h"

class Game {
public:
    Game(sf::RenderWindow& window, const sf::View& view, IResource& resource);

    void handleMainMenu(const sf::Event& event);
    void handlePauseMenu(const sf::Event& event);
    void handlePlayingState(const sf::Event& event);
    void handleGameOverState(const sf::Event& event);
    void initializeElements();
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
    std::unique_ptr<IAI> ai;

    UI ui;

    GameState state;
};

#endif // GAME_H
