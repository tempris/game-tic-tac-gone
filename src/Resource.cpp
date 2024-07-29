#include "Resource.h"
#include <iostream>

Resource::Resource() {
    font = std::make_unique<sf::Font>();
    brandTexture = std::make_unique<sf::Texture>();
    xTexture = std::make_unique<sf::Texture>();
    oTexture = std::make_unique<sf::Texture>();
    winTexture = std::make_unique<sf::Texture>();
    tieTexture = std::make_unique<sf::Texture>();

    if (!font->loadFromFile("Content/Font/NotoSans-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        throw std::runtime_error("Failed to load font: Content/Font/NotoSans-Regular.ttf");
    }

    if (!brandTexture->loadFromFile("Content/Image/Brand/Logo.png")) {
        std::cerr << "Failed to load Brand texture!" << std::endl;
        throw std::runtime_error("Failed to load texture: Content/Image/Brand/Logo.png");
    }

    if (!xTexture->loadFromFile("Content/Image/Interface/PlayerX.png")) {
        std::cerr << "Failed to load X texture!" << std::endl;
        throw std::runtime_error("Failed to load texture: Content/Image/Interface/PlayerX.png");
    }

    if (!oTexture->loadFromFile("Content/Image/Interface/PlayerO.png")) {
        std::cerr << "Failed to load O texture!" << std::endl;
        throw std::runtime_error("Failed to load texture: Content/Image/Interface/PlayerO.png");
    }

    if (!winTexture->loadFromFile("Content/Image/Interface/Win.png")) {
        std::cerr << "Failed to load Win texture!" << std::endl;
        throw std::runtime_error("Failed to load texture: Content/Image/Interface/Win.png");
    }

    if (!tieTexture->loadFromFile("Content/Image/Interface/Tie.png")) {
        std::cerr << "Failed to load Tie texture!" << std::endl;
        throw std::runtime_error("Failed to load texture: Content/Image/Interface/Tie.png");
    }

    moveSound = std::make_unique<sf::SoundBuffer>();
    if (!moveSound->loadFromFile("Content/Audio/Move.ogg")) {
        std::cerr << "Failed to load move sound!" << std::endl;
        throw std::runtime_error("Failed to load sound: Content/Audio/Move.ogg");
    }
}

Resource& Resource::getInstance() {
    static Resource instance;
    return instance;
}

sf::Font& Resource::getFont() {
    return *font;
}

sf::Texture& Resource::getBrandTexture() {
    return *brandTexture;
}

sf::Texture& Resource::getXTexture() {
    return *xTexture;
}

sf::Texture& Resource::getOTexture() {
    return *oTexture;
}

sf::Texture& Resource::getWinTexture() {
    return *winTexture;
}

sf::Texture& Resource::getTieTexture() {
    return *tieTexture;
}

sf::SoundBuffer& Resource::getMoveSound() {
    return *moveSound;
}