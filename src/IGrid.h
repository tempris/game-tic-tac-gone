#ifndef IGRID_H
#define IGRID_H

#include "Shared.h"
#include <SFML/Graphics.hpp>

class IGrid {
public:
    virtual ~IGrid() = default;
    virtual bool isCellEmpty(int row, int col) const = 0;
    virtual void setCell(int row, int col, PlayerType player, bool trackMove = true) = 0;
    virtual PlayerType getCell(int row, int col) const = 0;
    virtual bool isFull() const = 0;
    virtual int countEmptyCells() const = 0;
    virtual bool checkWin(PlayerType player) const = 0;
    virtual void initialize() = 0;
    virtual bool handleClick(int x, int y, PlayerType& currentPlayer) = 0;
    virtual void draw(sf::RenderWindow& window, bool canHover = true) const = 0;
    virtual void updateSize(float windowWidth, float windowHeight) = 0;
};

#endif // IGRID_H
