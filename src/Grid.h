#ifndef GRID_H
#define GRID_H

#include "Shared.h"
#include "IPlayer.h"
#include <SFML/Graphics.hpp>

class Grid {
public:
    Grid();

    bool isCellEmpty(int row, int col) const;
    void setCell(int row, int col, PlayerType player);
    PlayerType getCell(int row, int col) const;
    bool isFull() const;
    bool checkWin(PlayerType player) const;
    void initialize();
    bool handleClick(int x, int y, PlayerType& currentPlayer);
    void draw(sf::RenderWindow& window, sf::Font& font) const;
    void updateSize(float windowWidth, float windowHeight);

private:
    PlayerType cells[gridSize][gridSize];
    float cellSize;
    float offsetX;
    float offsetY;
};

#endif // GRID_H
