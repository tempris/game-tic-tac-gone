#include "Window.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), title), view(sf::FloatRect(0, 0, width, height)) {
    window.setView(view);
}

void Window::updateView() {
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
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
