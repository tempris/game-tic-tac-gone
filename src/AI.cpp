#include "AI.h"
#include <algorithm>

AI::AI(PlayerType aiPlayer, PlayerType humanPlayer)
    : aiPlayer(aiPlayer), humanPlayer(humanPlayer) {}

void AI::makeMove(Grid& grid) {
    int bestVal = std::numeric_limits<int>::min();
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid.isCellEmpty(i, j)) {
                grid.setCell(i, j, aiPlayer);
                int moveVal = minimax(grid, 0, false);
                grid.setCell(i, j, PlayerType::None);

                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    grid.setCell(bestMoveRow, bestMoveCol, aiPlayer);
}

int AI::minimax(Grid& grid, int depth, bool isMaximizing) {
    int score = evaluateGrid(grid);

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;
    if (!isMovesLeft(grid))
        return 0;

    if (isMaximizing) {
        int best = std::numeric_limits<int>::min();

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid.isCellEmpty(i, j)) {
                    grid.setCell(i, j, aiPlayer);
                    best = std::max(best, minimax(grid, depth + 1, false));
                    grid.setCell(i, j, PlayerType::None);
                }
            }
        }
        return best;
    }
    else {
        int best = std::numeric_limits<int>::max();

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid.isCellEmpty(i, j)) {
                    grid.setCell(i, j, humanPlayer);
                    best = std::min(best, minimax(grid, depth + 1, true));
                    grid.setCell(i, j, PlayerType::None);
                }
            }
        }
        return best;
    }
}

int AI::evaluateGrid(const Grid& grid) {
    if (grid.checkWin(aiPlayer))
        return 10;
    if (grid.checkWin(humanPlayer))
        return -10;
    return 0;
}

bool AI::isMovesLeft(const Grid& grid) {
    return !grid.isFull();
}
