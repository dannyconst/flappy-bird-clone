#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main() {
    srand(time(NULL));
    Game game;

    // Game loop
    while (game.isRunning()) {
        game.update();
        game.render();
    }

    return 0;
}