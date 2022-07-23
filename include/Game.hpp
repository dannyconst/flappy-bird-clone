#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Bird.hpp"
#include "Ground.hpp"
#include "Pipe.hpp"

class Game {
    private:
        // Window
        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        sf::Event event;
        int fps;

        // Game logic
        bool gameOver;
        int points;
        float spawnTimerMax;
        float spawnTimer;

        // Game objects
        Bird bird;
        Ground ground;
        Pipe pipe;
        std::vector<Pipe> pipes;

        // Score UI
        sf::Font font;
        sf::Text scoreText;

        // Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Initializers
        void initVariables();
        void initWindow();
        void initFont();
        void initText();
        void initGameObjects();

    public:
        // Constructor/destructor
        Game();
        ~Game();

        // Getters
        bool isRunning();
        
        // Functions
        void pollEvents();
        void spawnPipes();
        void restart();

        // Update
        void updateInput();
        void updateMousePos();
        void updatePipes();
        void updateUI();
        void updateCollision();
        void update();

        // Render
        void render();
};