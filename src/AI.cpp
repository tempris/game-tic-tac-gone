#include "AI.h"
#include <iostream>

AI::AI(PlayerType aiPlayer, PlayerType humanPlayer)
    : aiPlayer(aiPlayer), humanPlayer(humanPlayer) {}

void AI::makeMove(IGrid& grid) {
    int bestMove = -1;
    int bestValue = std::numeric_limits<int>::min();
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            if (grid.isCellEmpty(row, col)) {
                grid.setCell(row, col, aiPlayer);
                int moveValue = minimax(grid, 0, false);
                grid.setCell(row, col, PlayerType::None);
                if (moveValue > bestValue) {
                    bestMove = row * gridSize + col;
                    bestValue = moveValue;
                }
            }
        }
    }
    if (bestMove != -1) {
        int row = bestMove / gridSize;
        int col = bestMove % gridSize;
        if (grid.isCellEmpty(row, col)) {  // Double-check if the chosen cell is still empty
            grid.setCell(row, col, aiPlayer);
        }
        else {
            std::cerr << "AI error: Attempted to place on a non-empty cell or out of bounds." << std::endl;
        }
    }
    else {
        std::cerr << "AI error: No valid moves available." << std::endl;
    }
}

int AI::minimax(IGrid& grid, int depth, bool isMaximizing) {
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

int AI::evaluateGrid(const IGrid& grid) {
    if (grid.checkWin(aiPlayer))
        return 10;
    if (grid.checkWin(humanPlayer))
        return -10;
    return 0;
}

bool AI::isMovesLeft(const IGrid& grid) {
    return !grid.isFull();
}
