#ifndef GRID_H
#define GRID_H

#include <deque>
#include <utility>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "IGrid.h"
#include "Shared.h"

class Grid : public IGrid {
public:
    Grid();

    std::deque<std::pair<int, int>> lastThreeCellsPlayer1;
    std::deque<std::pair<int, int>> lastThreeCellsPlayer2;

    bool isCellEmpty(int row, int col) const override;
    void setCell(int row, int col, PlayerType player, bool trackMove = true) override;
    PlayerType getCell(int row, int col) const override;
    bool isFull() const override;
    int countEmptyCells() const override;
    bool checkWin(PlayerType player) const override;
    void initialize() override;
    void setClassic(bool enable = false);
    bool handleClick(int x, int y, PlayerType& currentPlayer) override;
    void draw(sf::RenderWindow& window, bool canHover = true) const override;
    void updateSize(float windowWidth, float windowHeight) override;

private:
    PlayerType cells[gridSize][gridSize];
    float cellSize;
    float offsetX;
    float offsetY;
    bool classic = true;

    sf::Sound sound;

    mutable std::vector<std::pair<int, int>> winningCells;
};

#endif // GRID_H
