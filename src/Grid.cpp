#include <iostream>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Resource.h"

Grid::Grid() {
    initialize();

    sound.setBuffer(Resource::getInstance().getMoveSound());
    sound.setVolume(25.0f);
}

bool Grid::isCellEmpty(int row, int col) const {
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        std::cerr << "Invalid cell position (" << row << ", " << col << ")" << std::endl;
        return false;
    }
    return cells[row][col] == PlayerType::None;
}

void Grid::setCell(int row, int col, PlayerType player, bool trackMove) {
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        std::cerr << "Invalid cell position (" << row << ", " << col << ")" << std::endl;
        return;
    }

    // Set the new cell
    cells[row][col] = player;

    if (trackMove && !classic) {
        auto& playerDeque = (player == PlayerType::Player1) ? lastThreeCellsPlayer1 : lastThreeCellsPlayer2;

        // Keep only the last three moves
        if (playerDeque.size() == 3) {
            auto oldestCell = playerDeque.front();
            // Set the oldest cell to None before removing it from the deque
            if (oldestCell.first >= 0 && oldestCell.first < gridSize &&
                oldestCell.second >= 0 && oldestCell.second < gridSize) {
                cells[oldestCell.first][oldestCell.second] = PlayerType::None;
            }
            playerDeque.pop_front();  // Remove the oldest entry
        }
        playerDeque.push_back({ row, col });  // Add the new move
    }

    if (trackMove || player == PlayerType::Player1) {
        sound.play();
    }
}

PlayerType Grid::getCell(int row, int col) const {
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        std::cerr << "Invalid cell position (" << row << ", " << col << ")" << std::endl;
        return PlayerType::None;
    }
    return cells[row][col];
}

bool Grid::isFull() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (isCellEmpty(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int Grid::countEmptyCells() const {
    int emptyCount = 0;
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            if (cells[row][col] == PlayerType::None) {
                emptyCount++;
            }
        }
    }
    return emptyCount;
}

bool Grid::checkWin(PlayerType player) const {
    winningCells.clear();  // Clear previous winning cells
    for (int i = 0; i < gridSize; ++i) {
        if (cells[i][0] == player && cells[i][1] == player && cells[i][2] == player) {
            winningCells.push_back({ i, 0 });
            winningCells.push_back({ i, 1 });
            winningCells.push_back({ i, 2 });
            return true;
        }
        if (cells[0][i] == player && cells[1][i] == player && cells[2][i] == player) {
            winningCells.push_back({ 0, i });
            winningCells.push_back({ 1, i });
            winningCells.push_back({ 2, i });
            return true;
        }
    }
    if (cells[0][0] == player && cells[1][1] == player && cells[2][2] == player) {
        winningCells.push_back({ 0, 0 });
        winningCells.push_back({ 1, 1 });
        winningCells.push_back({ 2, 2 });
        return true;
    }
    if (cells[0][2] == player && cells[1][1] == player && cells[2][0] == player) {
        winningCells.push_back({ 0, 2 });
        winningCells.push_back({ 1, 1 });
        winningCells.push_back({ 2, 0 });
        return true;
    }
    return false;
}

void Grid::setClassic(bool enable) {
    classic = enable;
}

void Grid::initialize() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cells[i][j] = PlayerType::None;
        }
    }

    // Clear the move tracking deques for both players
    lastThreeCellsPlayer1.clear();
    lastThreeCellsPlayer2.clear();

    winningCells.clear();  // Clear previous winning cells
}

bool Grid::handleClick(int x, int y, PlayerType& currentPlayer) {
    int col = static_cast<int>((x - offsetX) / cellSize);
    int row = static_cast<int>((y - offsetY) / cellSize);

    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        std::cerr << "Click out of bounds (" << x << ", " << y << ")" << std::endl;
        return false;
    }

    if (isCellEmpty(row, col)) {
        setCell(row, col, currentPlayer);
        return true;
    }
    return false;
}

void Grid::draw(sf::RenderWindow& window, bool canHover) const {
    sf::RectangleShape cellBackground(sf::Vector2f(cellSize, cellSize));
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cellBackground.setPosition(offsetX + j * cellSize, offsetY + i * cellSize);

            // Highlight cell if it's part of the winning combination
            if (std::find(winningCells.begin(), winningCells.end(), std::make_pair(i, j)) != winningCells.end()) {
                cellBackground.setFillColor(sf::Color(255, 255, 0, 128)); // Light yellow for winning cells
            }
            else if (canHover && cellBackground.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                cellBackground.setFillColor(sf::Color(200, 200, 200, 128)); // Light gray for hover
            }
            else {
                cellBackground.setFillColor(sf::Color(255, 255, 255, 10)); // Transparent
            }

            window.draw(cellBackground);
        }
    }

    sf::RectangleShape line(sf::Vector2f(cellSize * gridSize, 8)); // Thicker lines
    line.setFillColor(sf::Color(200, 200, 200)); // Light gray color
    for (int i = 1; i < gridSize; ++i) {
        line.setPosition(offsetX, offsetY + i * cellSize);
        window.draw(line);
        line.setSize(sf::Vector2f(8, cellSize * gridSize)); // Adjust width for vertical lines
        line.setPosition(offsetX + i * cellSize, offsetY);
        window.draw(line);
        line.setSize(sf::Vector2f(cellSize * gridSize, 8)); // Reset size for horizontal lines
    }

    sf::Sprite sprite;
    float padding = 30.0f;  // Padding of 30 pixels on each side
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            PlayerType cell = getCell(i, j);
            if (cell != PlayerType::None) {
                if (cell == PlayerType::Player1) {
                    sprite.setTexture(Resource::getInstance().getXTexture());
                }
                else if (cell == PlayerType::Player2) {
                    sprite.setTexture(Resource::getInstance().getOTexture());
                }

                // Set half transparency for the third oldest cell
                auto& playerDeque = (cell == PlayerType::Player1) ? lastThreeCellsPlayer1 : lastThreeCellsPlayer2;
                if (!classic && playerDeque.size() == 3 && std::make_pair(i, j) == playerDeque.front()) {
                    sprite.setColor(sf::Color(255, 255, 255, 128)); // Half transparent
                }
                else {
                    sprite.setColor(sf::Color(255, 255, 255, 255)); // Fully opaque
                }

                // Adjust position and scale for padding
                float paddedPositionX = offsetX + j * cellSize + padding / 2;
                float paddedPositionY = offsetY + i * cellSize + padding / 2;
                float paddedCellSize = cellSize - padding;  // Reduce cell size by padding on both sides

                sprite.setPosition(paddedPositionX, paddedPositionY);
                sprite.setScale(paddedCellSize / sprite.getLocalBounds().width, paddedCellSize / sprite.getLocalBounds().height);

                window.draw(sprite);
            }
        }
    }
}

void Grid::updateSize(float windowWidth, float windowHeight) {
    cellSize = std::min(windowWidth, windowHeight) / gridSize;
    offsetX = (windowWidth - cellSize * gridSize) * 0.5f;
    offsetY = (windowHeight - cellSize * gridSize) * 0.5f;
}
