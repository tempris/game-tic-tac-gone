#ifndef AI_H
#define AI_H

#include "Grid.h"
#include "Player.h"
#include "GameDefinitions.h"

class AI {
public:
    AI(PlayerType aiPlayer, PlayerType humanPlayer);

    void makeMove(Grid& grid);

private:
    PlayerType aiPlayer;
    PlayerType humanPlayer;

    int minimax(Grid& grid, int depth, bool isMaximizing);
    int evaluateGrid(const Grid& grid);
    bool isMovesLeft(const Grid& grid);
};

#endif // AI_H