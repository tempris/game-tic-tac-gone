#ifndef GRID_H
#define GRID_H

#include "IGrid.h"
#include "Shared.h"
#include <SFML/Graphics.hpp>

class Grid : public IGrid {
public:
    Grid();

    bool isCellEmpty(int row, int col) const override;
    void setCell(int row, int col, PlayerType player) override;
    PlayerType getCell(int row, int col) const override;
    bool isFull() const override;
    bool checkWin(PlayerType player) const override;
    void initialize() override;
    bool handleClick(int x, int y, PlayerType& currentPlayer) override;
    void draw(sf::RenderWindow& window, sf::Font& font) const override;
    void updateSize(float windowWidth, float windowHeight) override;

private:
    PlayerType cells[gridSize][gridSize];
    float cellSize;
    float offsetX;
    float offsetY;
};

#endif // GRID_H
