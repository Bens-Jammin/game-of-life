#include <iostream>
#include "game.hpp"
#include "patterns/patterns.hpp"




void demo1() {
    GameEngine game(false);
    game.fullscreen();
    game.setTickRateMS(100);

    stillife_block(game, 60, 10);
    
    oscillator_blinker(game, 10, 10);

    spaceship_glider(game, 80, 4);
    // spaceship_glider(game, 200, 20);

    oscillator_toad(game, 20, 10);
    oscillator_pulsar(game, 100, 10);

    game.run();

}

int main() {
    GameEngine game(false);
    game.fullscreen();
    game.setTickRateMS(10);

    stillife_block(game, 60, 10);
    
    oscillator_blinker(game, 10, 10);
    oscillator_blinker(game, 10, 30);

    spaceship_glider(game, 80, 4);
    
    oscillator_toad(game, 90, 10);
    oscillator_pulsar(game, 75, 10);

    gun_long(game, 40, 20);
    gun_long(game, 100, 20);

    game.run();
}