#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class Window {
public:
    using EventCallback = std::function<void(const sf::Event&)>;

    Window(const std::string& title, unsigned int width, unsigned int height);

    void updateView();
    void handleEvents();
    bool isOpen() const;
    void clear();
    void display();
    sf::RenderWindow& getRenderWindow();

    void onResize(const std::function<void()>& callback);
    void onEvent(const EventCallback& callback);

private:
    void setIcon();
    
    sf::RenderWindow window;
    sf::View view;
    std::vector<std::function<void()>> resizeCallbacks;
    std::vector<EventCallback> eventCallbacks;
};

#endif // WINDOW_H
