#include "Grid.h"

Grid::Grid() {
    initialize();
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

void Grid::initialize() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cells[i][j] = PlayerType::None;
        }
    }
}

bool Grid::handleClick(int x, int y, PlayerType& currentPlayer) {
    int row = static_cast<int>((y - offsetY) / cellSize);
    int col = static_cast<int>((x - offsetX) / cellSize);
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize && isCellEmpty(row, col)) {
        setCell(row, col, currentPlayer);
        currentPlayer = (currentPlayer == PlayerType::Player1) ? PlayerType::Player2 : PlayerType::Player1;
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
                text.setFillColor(cell == PlayerType::Player1 ? sf::Color::Red : sf::Color::Blue); // Different colors for players

                // Set the position of the text
                text.setPosition(offsetX + j * cellSize + cellSize * 0.1f, offsetY + i * cellSize);
                text.setScale(1.0f, 1.0f);

                window.draw(text);
            }
        }
    }
}

void Grid::updateSize(float windowWidth, float windowHeight) {
    cellSize = std::min(windowWidth, windowHeight) / gridSize;
    offsetX = (windowWidth - cellSize * gridSize) / 2.0f;
    offsetY = (windowHeight - cellSize * gridSize) / 2.0f;
}
