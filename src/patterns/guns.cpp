// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Pattern_taxonomy

#include "patterns.hpp"


// coordinate is top of blinker when vertical
void gun_long(GameEngine& board, int x, int y) {
    board.setMany({
        {x,y,true}, {x+1,y,true}, {x+2,y,true}, {x+3,y,true}, {x+4,y,true}, {x+5,y,true}, {x+6,y,true}, {x+7,y,true},
        {x+9,y,true}, {x+10,y,true}, {x+11,y,true}, {x+12,y,true}, {x+13,y,true},
        {x+17,y,true}, {x+18,y,true}, {x+19,y,true},
        {x+26,y,true}, {x+27,y,true}, {x+28,y,true}, {x+29,y,true}, {x+30,y,true}, {x+31,y,true}, {x+32,y,true},
        {x+34,y,true}, {x+35,y,true}, {x+36,y,true}, {x+37,y,true}, {x+38,y,true}
    });
}
