#ifndef AI_H
#define AI_H

#include "IAI.h"
#include "Grid.h"
#include "Player.h"
#include "Shared.h"

class AI : public IAI {
public:
    AI(PlayerType aiPlayer, PlayerType humanPlayer);
    void makeMove(Grid& grid) override;

private:
    PlayerType aiPlayer;
    PlayerType humanPlayer;

    int minimax(Grid& grid, int depth, bool isMaximizing);
    int evaluateGrid(const Grid& grid);
    bool isMovesLeft(const Grid& grid);
};

#endif // AI_H
