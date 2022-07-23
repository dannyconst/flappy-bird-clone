#include "Pipe.hpp"

void Pipe::initShape() {
    shape.setFillColor(sf::Color::Blue);
}

Pipe::Pipe() {
    initShape();
}

Pipe::~Pipe() {}

void Pipe::update() {
    shape.move(sf::Vector2f(-scrollSpeed, 0.f));
}

void Pipe::render(sf::RenderTarget* target) {
    target->draw(shape);
}