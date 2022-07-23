#pragma once
#include <SFML/Graphics.hpp>
#include "Pipe.hpp"

class Bird {
    private:
        float yVel;
        float force = 8.f;

        sf::Texture texture;

        // Keyboard keys
        bool spaceKeyHeld = false;

    public:
        sf::RectangleShape shape;
        bool gameOver = false;

        Bird();
        Bird(sf::RenderTarget* window);
        ~Bird();

        // Initializers
        void initShape(sf::RenderTarget* window);

        bool getGameOverStatus();

        void updateInput(sf::RenderTarget* window);
        void updateVelocity();
        void updateCollision(sf::RenderTarget* window);
        void update(sf::RenderTarget* window);
        void render(sf::RenderTarget* target);
};