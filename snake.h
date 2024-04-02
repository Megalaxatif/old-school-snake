#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

class Snake{
    public:
        Snake();
        void init_board();
        void draw_board();
        void spawn_apple();
        void check_collision();
        void move_snake();
    private:
        int snake_length;
        int apple_posx;
        int apple_posy;
        int posx;
        int posy;
        int x_array[100];
        int y_array[100];
        int board_length;
        int board_heigth;
        int board[10][10];

};
#endif