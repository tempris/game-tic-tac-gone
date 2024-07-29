#include "Window.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), title), view(sf::FloatRect(0, 0, static_cast<float>(width), static_cast<float>(height))) {
    window.setView(view);
    setIcon();
}

void Window::setIcon() {
    sf::Image icon;
    if (icon.loadFromFile("Content/Image/Brand/Icon16.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

void Window::updateView() {
    view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    view.setCenter(static_cast<float>(window.getSize().x) * 0.5f, static_cast<float>(window.getSize().y) * 0.5f);
    window.setView(view);
}

void Window::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::Resized) {
            updateView();
            for (const auto& callback : resizeCallbacks) {
                callback();
            }
        }
        for (const auto& callback : eventCallbacks) {
            callback(event);
        }
    }
}

bool Window::isOpen() const {
    return window.isOpen();
}

void Window::clear() {
    window.clear();
}

void Window::display() {
    window.display();
}

sf::RenderWindow& Window::getRenderWindow() {
    return window;
}

void Window::onResize(const std::function<void()>& callback) {
    resizeCallbacks.push_back(callback);
}

void Window::onEvent(const EventCallback& callback) {
    eventCallbacks.push_back(callback);
}
