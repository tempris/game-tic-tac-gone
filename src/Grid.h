#ifndef GRID_H
#define GRID_H

#include "GameDefinitions.h"
#include "Player.h"

class Grid {
public:
    Grid();

    bool isCellEmpty(int row, int col) const;
    void setCell(int row, int col, PlayerType player);
    PlayerType getCell(int row, int col) const;
    bool isFull() const;
    bool checkWin(PlayerType player) const;

private:
    PlayerType cells[gridSize][gridSize];
};

#endif // GRID_H
