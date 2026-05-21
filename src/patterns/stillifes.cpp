// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Pattern_taxonomy

#include "patterns.hpp"


// coordinate is top left of square
void stillife_block(GameEngine& board, int x, int y) {
    board.set(x  , y  , true);
    board.set(x  , y+1, true);
    board.set(x+1, y  , true);
    board.set(x+1, y+1, true);
}