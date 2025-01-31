#ifndef GAME_H
#define GAME_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "IGrid.h"
#include "Player.h"
#include "IAI.h"
#include "Shared.h"
#include "UI.h"
#include "IResource.h"

class Game {
public:
    Game(sf::RenderWindow& window, const sf::View& view, std::unique_ptr<IGrid> grid, std::unique_ptr<IAI> ai, IResource& resource);

    void handlePlayingState(const sf::Event& event);
    void resizeElements();
    void initializeElements();
    void draw();
    void handleEvent(const sf::Event& event);
    void triggerAIMove();
    void updateGameLogic();

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

    PlayerType currentPlayer;
    PlayerType winner;

    std::unique_ptr<IGrid> grid;
    std::unique_ptr<IAI> ai;

    UI ui;

    GameState state;

    sf::Clock aiMoveDelayClock;
    bool aiMoveScheduled = false;
    float aiMoveDelayDuration;
};

#endif // GAME_H
