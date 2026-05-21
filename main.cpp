#include <iostream>
#include "game.hpp"
#include "patterns/patterns.hpp"


int main() {
    GameEngine game(false);
    game.setTickRateMS(100);

    stillife_block(game, 4, 0);
    
    oscillator_blinker(game, 10, 10);

    spaceship_glider(game, 0, 5);

    game.run();
}