#pragma once
#include <vector>

#define DEFAULT_WIDTH  25
#define DEFAULT_HEIGHT 25

#define ALIVE_CHAR "X"
#define DEAD_CHAR "."


class GameEngine {
    private:
        int width;
        int height;
        long tick;
        long liveCellCount;
        long tickRateMS;
        std::vector<bool> board;
    public:
        GameEngine();
        GameEngine(bool generateBoard);
        GameEngine(int w, int h, bool generateBoard);

        void setTickRateMS(long ms);
        bool get(int x, int y);
        void set(int x, int y, bool val);
        int neighbourCount(int x, int y);
        void display();
        void clearScreen();
        void randomStart();
        void step();
        void run();
};


bool randomBool();