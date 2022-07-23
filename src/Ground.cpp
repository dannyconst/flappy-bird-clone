#include "Ground.hpp"

void Ground::initShape(sf::RenderTarget* window) {
    shape.setSize(sf::Vector2f(window->getSize().x, 100.f));
    shape.setPosition(sf::Vector2f(window->getSize().x / 2.f - shape.getSize().x / 2.f, window->getSize().y - shape.getSize().y));
    shape.setFillColor(sf::Color(170, 219, 30));
}

Ground::Ground() {}

Ground::Ground(sf::RenderTarget* window) {
    initShape(window);
}

Ground::~Ground() {}

void Ground::render(sf::RenderTarget* target) {
    target->draw(shape);
}