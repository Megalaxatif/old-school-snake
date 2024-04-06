#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

enum class INDEX{
    EMPTY_SPACE = 0,
    BORDER = 1,
    FRUIT = 2,
    SNAKE = 3
};

class Snake{
    public:
        Snake(HANDLE console);
        void goto_(int x, int y);
        void init_board();
        void draw_board();
        void draw_snake();
        void spawn_apple();
        bool input_handler();
        bool move_snake();
    private:
        HANDLE console;
        unsigned int snake_length;
        int posx, posy;
        int dirx, diry;
        const int board_posx = 10;
        const int board_posy = 10;
        int x_array[100];
        int y_array[100];
        int apple_posx;
        int apple_posy;
        int board_length;
        int board_heigth;
        int board[15][15];

};
#endif