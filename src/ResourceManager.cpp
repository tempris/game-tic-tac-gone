#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
    font = std::make_unique<sf::Font>();
    if (!font->loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

sf::Font& ResourceManager::getFont() {
    return *font;
}
