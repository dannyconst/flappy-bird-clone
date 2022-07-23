#include "Game.hpp"

void Game::initVariables() {
    // Window
    window = nullptr;
    fps = 60;

    // Game logic
    gameOver = false;
    points = -1;
    spawnTimerMax = 100.f;
    spawnTimer = spawnTimerMax;
}

void Game::initWindow() {
    // Window size
    videoMode.width = 400;
    videoMode.height = 600;

    // Create window
    window = new sf::RenderWindow(videoMode, "My window", sf::Style::Close);
    
    // Center the window
    window->setPosition(sf::Vector2i(
        (videoMode.getDesktopMode().width / 2) - videoMode.width / 2,
        (videoMode.getDesktopMode().height / 2) - videoMode.height / 2)
    );

    // Cap the framerate
    window->setFramerateLimit(fps);
}

void Game::initFont() {
    if (!font.loadFromFile("assets/fonts/game_over.ttf")) {
        std::cout << "Failed to load game over font\n";
    }
}

void Game::initText() {
    scoreText.setFont(font);
    scoreText.setString("Score:");
    scoreText.setCharacterSize(72);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(sf::Vector2f(20.f, 0.f));
}

void Game::initGameObjects() {
    bird = Bird(window);
    ground = Ground(window);
}

Game::Game() {
    initVariables();
    initWindow();
    initFont();
    initText();
    initGameObjects();
}

Game::~Game() {
    delete window;
}

bool Game::isRunning() {
    return window->isOpen();
}

void Game::pollEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Game::spawnPipes() {
    int type = rand() % 4;
    
    // Pipe 1
    switch (type) {
        case 0:
            pipe.shape.setSize(sf::Vector2f(50.f, 350.f));
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 680.f));
            break;
        
        case 1:
            pipe.shape.setSize(sf::Vector2f(50.f, 300.f));
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 715.f));
            break;
        
        case 2:
            pipe.shape.setSize(sf::Vector2f(50.f, 170.f));
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 650.f));
            break;
        
        case 3:
            pipe.shape.setSize(sf::Vector2f(50.f, 100.f));
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 650.f));
            break;

        default:
            break;
    }
    pipes.push_back(pipe);

    // Pipe 2
    pipe.shape.setSize(sf::Vector2f(50.f, 250.f));

    switch (type) {
        case 0:
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 150.f));
            break;
        
        case 1:
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 250.f));
            break;
        
        case 2:
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 300.f));
            break;
        
        case 3:
            pipe.shape.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y - 350.f));
            break;

        default:
            break;
    }
    pipes.push_back(pipe);
}

void Game::restart() {
    points = -1;
    spawnTimer = spawnTimerMax;
    bird.initShape(window);
    gameOver = false;
    bird.gameOver = false;

    for (int i = 0; i < pipes.size(); i++) {
        pipes.erase(pipes.begin() + i);
    }
}

void Game::updateInput() {
    if (gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            restart();
        }
    }
}

void Game::updateMousePos() {
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updatePipes() {
    if (spawnTimer >= spawnTimerMax) {
        // Spawn and reset
        spawnPipes();
        points++;

        spawnTimer = 0.f;
    }
    else {
        spawnTimer += 1.f;
    }

    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].update();

        if (pipes[i].shape.getPosition().x <= -50.f) {
            pipes.erase(pipes.begin() + i);
        }
    }
}

void Game::updateUI() {
     std::stringstream text;

    text << "Score: " << points << std::endl;
        
    if (gameOver) {
        text << "Game Over\n";
        text << "Press \"R\" to restart\n";
    }

    scoreText.setString(text.str());
}

void Game::updateCollision() {
    for (int i = 0; i < pipes.size(); i++) {
        if (bird.shape.getGlobalBounds().intersects(pipes[i].shape.getGlobalBounds())) {
            gameOver = true;
            bird.gameOver = true;
        }
    }
}

void Game::update() {
    pollEvents();

    updateInput();
    
    if (!gameOver) {
        updateMousePos();
        updatePipes();
        updateCollision();
        
        gameOver = bird.getGameOverStatus();
    }

    updateUI();
    
    bird.update(window);
}

void Game::render() {
    // Refresh
    window->clear(sf::Color(135, 206, 235));

    // Draw game objects
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].render(window);
    }

    ground.render(window);
    bird.render(window);

    // UI
    window->draw(scoreText);

    // Display
    window->display();
}