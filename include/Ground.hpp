#pragma once
#include <SFML/Graphics.hpp>

class Ground {
    private:
        sf::RectangleShape shape;

        void initShape(sf::RenderTarget* window);

    public:
        Ground();
        Ground(sf::RenderTarget* window);
        ~Ground();

        void render(sf::RenderTarget* target);
};