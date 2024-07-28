#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>

class Resource {
public:
    static Resource& getInstance();
    sf::Font& getFont();

private:
    Resource();
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;

    std::unique_ptr<sf::Font> font;
};

#endif // RESOURCE_MANAGER_H
