// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Pattern_taxonomy

#include "patterns.hpp"


// coordinate is top of blinker when vertical
void oscillator_blinker(GameEngine& board, int x, int y) {
    board.setMany({{x, y  , true}, {x, y-1, true}, {x, y-2, true}});
}


// coordinate is bottom left corner
void oscillator_toad(GameEngine& board, int x, int y) {
    board.setMany({
        {x, y, true}, 
        {x+1, y, true}, 
        {x+2, y, true}, 
        {x+1, y-1, true}, 
        {x+2, y-1, true}, 
        {x+3, y-1, true}
    });
}

// coordinate is left pixel of top left bar
void oscillator_pulsar(GameEngine& board, int x, int y) {
    board.setMany({
        {x, y, true}, {x+1, y, true}, {x+2, y, true}, {x+6, y, true}, {x+7, y, true}, {x+8, y, true},
        {x-2,y+2, true}, {x-2,y+3, true}, {x-2,y+4, true}, 
        {x+3,y+2, true}, {x+3,y+3, true}, {x+3,y+4, true}, 
        {x+5,y+2, true}, {x+5,y+3, true}, {x+5,y+4, true},
        {x+10,y+2, true}, {x+10,y+3, true}, {x+10,y+4, true},
        {x, y+5, true}, {x+1, y+5, true}, {x+2, y+5, true}, {x+6, y+5, true}, {x+7, y+5, true}, {x+8, y+5, true},
        {x, y+7, true}, {x+1, y+7, true}, {x+2, y+7, true}, {x+6, y+7, true}, {x+7, y+7, true}, {x+8, y+7, true},
        {x-2,y+8, true}, {x-2,y+9, true}, {x-2,y+10, true}, 
        {x+3,y+8, true}, {x+3,y+9, true}, {x+3,y+10, true}, 
        {x+5,y+8, true}, {x+5,y+9, true}, {x+5,y+10, true},
        {x+10,y+8, true}, {x+10,y+9, true}, {x+10,y+10, true},
        {x, y+12, true}, {x+1, y+12, true}, {x+2, y+12, true}, {x+6, y+12, true}, {x+7, y+12, true}, {x+8, y+12, true}
    });
}