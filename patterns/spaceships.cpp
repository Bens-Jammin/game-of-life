// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Pattern_taxonomy

#include "patterns.hpp"


// coordinate is topleft-most diagonal at step=0
void spaceship_glider(GameEngine &board, int x, int y) {
    board.set(x  , y  , true);
    board.set(x+2, y-1, true);
    board.set(x+2, y  , true);
    board.set(x+1, y+1, true);
    board.set(x+2, y+1, true);
}