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
        Snake();
        void init_board();
        void draw_board();
        void spawn_apple();
        void input_handler();
        void move_snake(int dirx, int diry);
    private:
        int snake_length;
        int posx;
        int posy;
        int x_array[100];
        int y_array[100];
        int apple_posx;
        int apple_posy;
        int board_length;
        int board_heigth;
        int board[10][15];

};
#endif