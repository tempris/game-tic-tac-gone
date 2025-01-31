#ifndef AI_H
#define AI_H

#include "IAI.h"
#include "IGrid.h"
#include "Player.h"

class AI : public IAI {
public:
    AI(PlayerType aiPlayer, PlayerType humanPlayer);
    void makeMove(IGrid& grid);

private:
    PlayerType aiPlayer;
    PlayerType humanPlayer;

    int minimax(IGrid& grid, int depth, bool isMaximizing, int alpha, int beta);
    int evaluateGrid(const IGrid& grid);
    bool isMovesLeft(const IGrid& grid);
};

#endif // AI_H
