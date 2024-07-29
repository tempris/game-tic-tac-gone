#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>
#include <SFML/Audio.hpp>
#include "IResource.h"

class Resource : public IResource {
public:
    static Resource& getInstance();
    sf::Font& getFont() override;

    sf::Texture& getBrandTexture();
    sf::Texture& getXTexture();
    sf::Texture& getOTexture();
    sf::Texture& getWinTexture();
    sf::Texture& getTieTexture();

    sf::SoundBuffer& getMoveSound();

private:
    Resource();
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;

    std::unique_ptr<sf::Font> font;

    std::unique_ptr<sf::Texture> brandTexture;
    std::unique_ptr<sf::Texture> xTexture;
    std::unique_ptr<sf::Texture> oTexture;
    std::unique_ptr<sf::Texture> winTexture;
    std::unique_ptr<sf::Texture> tieTexture;

    std::unique_ptr<sf::SoundBuffer> moveSound;
};

#endif // RESOURCE_H
