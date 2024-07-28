#include "Resource.h"
#include <iostream>

Resource::Resource() {
    font = std::make_unique<sf::Font>();
    if (!font->loadFromFile("content/font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

Resource& Resource::getInstance() {
    static Resource instance;
    return instance;
}

sf::Font& Resource::getFont() {
    return *font;
}
