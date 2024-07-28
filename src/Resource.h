#ifndef RESOURCE_H
#define RESOURCE_H

#include "IResource.h"
#include <memory>

class Resource : public IResource {
public:
    static Resource& getInstance();
    sf::Font& getFont() override;

private:
    Resource();
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;

    std::unique_ptr<sf::Font> font;
};

#endif // RESOURCE_H
