#include "Grid.h"

Grid::Grid() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cells[i][j] = PlayerType::None;
        }
    }
}

bool Grid::isCellEmpty(int row, int col) const {
    return cells[row][col] == PlayerType::None;
}

void Grid::setCell(int row, int col, PlayerType player) {
    cells[row][col] = player;
}

PlayerType Grid::getCell(int row, int col) const {
    return cells[row][col];
}

bool Grid::isFull() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (cells[i][j] == PlayerType::None) {
                return false;
            }
        }
    }
    return true;
}

bool Grid::checkWin(PlayerType player) const {
    for (int i = 0; i < gridSize; ++i) {
        if (cells[i][0] == player && cells[i][1] == player && cells[i][2] == player)
            return true;
        if (cells[0][i] == player && cells[1][i] == player && cells[2][i] == player)
            return true;
    }
    if (cells[0][0] == player && cells[1][1] == player && cells[2][2] == player)
        return true;
    if (cells[0][2] == player && cells[1][1] == player && cells[2][0] == player)
        return true;
    return false;
}
