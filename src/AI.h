#ifndef AI_H
#define AI_H

#include "IAI.h"
#include "IGrid.h"
#include "Player.h"

class AI : public IAI {
public:
    AI(PlayerType aiPlayer, PlayerType humanPlayer);
    void makeMove(IGrid& grid) override;

private:
    PlayerType aiPlayer;
    PlayerType humanPlayer;

    int minimax(IGrid& grid, int depth, bool isMaximizing);
    int evaluateGrid(const IGrid& grid);
    bool isMovesLeft(const IGrid& grid);
};

#endif // AI_H
