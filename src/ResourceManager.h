#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>

class ResourceManager {
public:
    static ResourceManager& getInstance();
    sf::Font& getFont();

private:
    ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unique_ptr<sf::Font> font;
};

#endif // RESOURCE_MANAGER_H
