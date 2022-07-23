#include "Bird.hpp"

void Bird::initShape(sf::RenderTarget* window) {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setPosition(sf::Vector2f(window->getSize().x / 4.f, window->getSize().y / 2.f - shape.getSize().y / 2.f - 50.f));
    shape.setFillColor(sf::Color::Red);
    shape.setTexture(&texture);

    yVel = 0.f;
}

Bird::Bird() {}

Bird::Bird(sf::RenderTarget* window) {
    initShape(window);
}

Bird::~Bird() {}

bool Bird::getGameOverStatus() {
    return gameOver;
}

void Bird::updateInput(sf::RenderTarget* window) {
    if (!spaceKeyHeld) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            yVel = 0.f;
            yVel -= force;
            spaceKeyHeld = true;
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        spaceKeyHeld = false;
    }
}

void Bird::updateVelocity() {
    if (yVel < 10.f) {
        yVel += 0.5f;
    }
}

void Bird::updateCollision(sf::RenderTarget* window) {
    if (shape.getPosition().y <= -50) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, -50.f));
    }
    
    if (shape.getPosition().y >= window->getSize().y - 160.f) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, window->getSize().y - 160.f));
        gameOver = true;
    }
}

void Bird::update(sf::RenderTarget* window) {
    if (!gameOver) {
        updateInput(window);
    }

    updateCollision(window);
    updateVelocity();

    shape.move(sf::Vector2f(0.f, yVel));
}

void Bird::render(sf::RenderTarget* target) {
    target->draw(shape);
}