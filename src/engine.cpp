#include <iostream>
#include "game.hpp"
#include <thread>
#include <chrono>
#include <algorithm>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <tuple>

GameEngine::GameEngine(): GameEngine(DEFAULT_WIDTH, DEFAULT_HEIGHT, true) {}
GameEngine::GameEngine(bool generateBoard): GameEngine(DEFAULT_WIDTH, DEFAULT_HEIGHT, generateBoard) {}
GameEngine::GameEngine(int w, int h, bool generateBoard): width(w), height(h), tick(0), isFullScreen(false), headerLines(0) {
    board.assign(width * height, false);

    if (generateBoard) { randomStart(); }
}


void GameEngine::fullscreen() { 
    #ifdef _WIN32
        std::cout << "Not supported currently!\n"
    #elif __linux__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int rows = w.ws_row;
        int cols = w.ws_col;

        headerLines = 2;        // tick count and live cell count , cursor at botom 
        board.assign((rows - headerLines) * cols, false);
        width = cols;
        height = rows - headerLines;
        isFullScreen = true;

    #else
        std::cout << "Not supported currently!\n"
    #endif 
}

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
    if (x < 0 || x >= width || y < 0 || y >= height) {
        std::cout << "ERROR! accessing out of bounds! tried to access (" << x << "," << y << ") with range (width=[0," << width << "], height=[0," << height << "]).\n";
        return;
    }
    bool current = get(x,y);
    if (current != state) { board[y * width + x] = state; }
}
void GameEngine::setMany(std::vector<std::tuple<int, int, bool>> points) {
    for ( auto& [x, y, state] : points ) set(x, y, state);
}


void GameEngine::display() {
    if (isFullScreen) {
        std::cout << " generation = " << std::setfill(' ') << std::left << std::setw(8) << tick
                << " | tickrate (ms) = "   << std::left << std::setw(6) << tickRateMS
                << " | population = " << std::left << std::setw(8) << liveCellCount 
                << "\n";
    }
   
    for (int y = 0; y<height; y++) {
        for (int x =0; x < width; x++ ) {
            std::cout << ( get(x, y) ? ALIVE_CHAR : DEAD_CHAR );
        }

        if (!isFullScreen && y == 0) { std::cout << "     generation=" << tick; }
        if (!isFullScreen && y == 1) { std::cout << "     population=" << liveCellCount; }
        if (!isFullScreen && y == 2) { std::cout << "  tickrate (ms)=" << tickRateMS; }
        
        std::cout << "\n";
    }
}

void GameEngine::clearScreen() {
    int lines = height + headerLines;
    std::cout << "\033[" << lines << "A" << std::flush; 
}

int GameEngine::neighbourCount(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int newX = x + dx;
            int newY = y + dy;
            if (newX < 0 || newX >= width || newY < 0 || newY >= height) continue;
            count += get(newX, newY);
        }
    }
    return count;
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