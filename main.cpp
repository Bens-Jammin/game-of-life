#include <iostream>
#include "game.hpp"
#include "patterns/patterns.hpp"


int main() {
    GameEngine game(false);
    game.fullscreen();
    game.setTickRateMS(25);

    stillife_block(game, 60, 10);
    
    oscillator_blinker(game, 10, 10);

    spaceship_glider(game, 0, 20);
    spaceship_glider(game, 200, 20);

    game.run();
}