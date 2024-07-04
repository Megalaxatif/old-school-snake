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

enum class GAME_STATUS{
    GAME_PLAYING = 0,
    GAME_OVER = 1,
    GAME_PAUSE = 2,
    GAME_QUIT = 3
};

class Snake{
    public:
        Snake(HANDLE console);
        void goto_(int x, int y);
        void init_board();
        void draw_board();
        void draw_snake();
        void spawn_apple();
        void draw_snake_length();
        void input_handler();
        bool move_snake();
        GAME_STATUS get_game_status();
        void game_over();

    private:
        HANDLE console;
        unsigned int snake_length;
        int posx, posy;
        int dirx, diry;
        int x_array[100];
        int y_array[100];
        int apple_posx, apple_posy;
        int ath_posx, ath_posy;
        const int board_posx = 1;
        const int board_posy = 0;
        static const int board_length = 15;
        static const int board_heigth = 15;
        int board[board_length][board_heigth];
        GAME_STATUS game_status;
        bool is_key_enter_pressed;
};
#endif