#include "Resource.h"
#include <iostream>

Resource::Resource() {
    font = std::make_unique<sf::Font>();
    if (!font->loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        // Handle the error appropriately
        throw std::runtime_error("Failed to load font: content/font/NotoSans-Regular.ttf");
    }
}

Resource& Resource::getInstance() {
    static Resource instance;
    return instance;
}

sf::Font& Resource::getFont() {
    return *font;
}
