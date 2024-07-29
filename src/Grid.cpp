#include "Grid.h"
#include <iostream>

Grid::Grid() {
    initialize();
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

    if (trackMove) {
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

void Grid::initialize() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cells[i][j] = PlayerType::None;
        }
    }

    // Clear the move tracking deques for both players
    lastThreeCellsPlayer1.clear();
    lastThreeCellsPlayer2.clear();
}

bool Grid::handleClick(int x, int y, PlayerType& currentPlayer) {
    int col = (x - offsetX) / cellSize;
    int row = (y - offsetY) / cellSize;

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

void Grid::draw(sf::RenderWindow& window, sf::Font& font) const {
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

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned int>(cellSize * 0.8f));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            PlayerType cell = getCell(i, j);
            if (cell != PlayerType::None) {
                text.setString(cell == PlayerType::Player1 ? "X" : "O");

                auto& playerDeque = (cell == PlayerType::Player1) ? lastThreeCellsPlayer1 : lastThreeCellsPlayer2;
                if (playerDeque.size() == 3 && playerDeque.front().first == i && playerDeque.front().second == j) {
                    // Apply half brightness to the third oldest cell
                    text.setFillColor((cell == PlayerType::Player1 ? sf::Color(255, 0, 0, 128) : sf::Color(0, 0, 255, 128)));
                }
                else {
                    // Full brightness for other cells
                    text.setFillColor(cell == PlayerType::Player1 ? sf::Color::Red : sf::Color::Blue);
                }

                // Calculate the bounding box of the text
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                // Set the position of the text to be centered in the cell
                text.setPosition(
                    offsetX + j * cellSize + cellSize / 2.0f,
                    offsetY + i * cellSize + cellSize / 2.0f
                );

                window.draw(text);
            }
        }
    }
}

void Grid::updateSize(float windowWidth, float windowHeight) {
    cellSize = std::min(windowWidth, windowHeight) / gridSize;
    offsetX = (windowWidth - cellSize * gridSize) * 0.5f;
    offsetY = (windowHeight - cellSize * gridSize) * 0.5f;
}
