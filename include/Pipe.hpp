#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pipe {
    private:
        float scrollSpeed = 3.f;

    public:
        sf::RectangleShape shape;

        Pipe();
        ~Pipe();

        void initShape();

        void update();
        void render(sf::RenderTarget* target);
};