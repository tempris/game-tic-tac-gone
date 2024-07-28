#ifndef IRESOURCE_H
#define IRESOURCE_H

#include <SFML/Graphics.hpp>

class IResource {
public:
    virtual ~IResource() = default;
    virtual sf::Font& getFont() = 0;
};

#endif // IRESOURCE_H
