#include <iostream>
#include "game.hpp"
#include <thread>
#include <chrono>
#include <algorithm>

GameEngine::GameEngine(): GameEngine(DEFAULT_WIDTH, DEFAULT_HEIGHT, true) {}
GameEngine::GameEngine(bool generateBoard): GameEngine(DEFAULT_WIDTH, DEFAULT_HEIGHT, generateBoard) {}
GameEngine::GameEngine(int w, int h, bool generateBoard): width(w), height(h), tick(0) {
    board.assign(width * height, false);

    if (generateBoard) { randomStart(); }
}


// void GameEngine::fullscreen() { }

void GameEngine::setTickRateMS(long ms) { tickRateMS = ms; }

void GameEngine::randomStart() {
    for (int y = 0; y<height; y++) {
        for (int x =0; x < width; x++ ) {
            bool val = randomBool();
            set(x, y, val);
        }
    }
}

bool GameEngine::get(int x, int y)           { return board[y * width + x]; }
void GameEngine::set(int x, int y, bool state) { 
    bool current = get(x,y);
    if (current != state) { board[y * width + x] = state; }
}


void GameEngine::display() {
    for (int y = 0; y<height; y++) {
        for (int x =0; x < width; x++ ) {
            std::cout << ( get(x, y) ? ALIVE_CHAR : DEAD_CHAR );
        }

        if (y == 0) { std::cout << "  tick=" << tick; }
        if (y == 1) { std::cout << "  live cell count=" << liveCellCount; }
        std::cout << "\n";
    }
}

void GameEngine::clearScreen() {
    for (int x = 0; x<width; x++)  { std::cout << "\033[1D"; }
    for (int y = 0; y<height; y++) { std::cout << "\033[1A"; }
    std::cout << std::flush;

}

int GameEngine::neighbourCount(int x, int y) {
    return  get(x-1, y-1) + get(x, y-1) + get(x+1, y-1) +
            get(x-1, y) + /* skip */       get(x+1, y) +
            get(x-1, y+1) + get(x, y+1) + get(x+1, y+1);
}

void GameEngine::step() {
    // make the next board, put updated values, then replace
    // this stops issues where updating one cell changes the destiny of its neighbour
    std::vector<bool> nextBoard = board;

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {

            int count = neighbourCount(x,y);
            bool cell = get(x,y);
            bool nextState = cell;

            if      (cell && count < 2)   { nextState = false; }
            else if (cell && count > 3)   { nextState = false; }
            else if (!cell && count == 3) { nextState = true;  }

            nextBoard[y * width + x] = nextState;
        }
    }
    board = nextBoard; 

    liveCellCount = std::count(board.begin(), board.end(), true);
    tick++;
}


void GameEngine::run() {

    while(1) {
        step();
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(tickRateMS)); 
        clearScreen();
    }
}