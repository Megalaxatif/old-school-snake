#include "snake.h"


const char* ANSI_code[2] = {"\033[37m  \033[0m", "\033[37;47m@@\033[0m"};

Snake::Snake() : board{ 0 }
{
    srand((unsigned)time(NULL));
    board_length = 10;
    board_heigth = 10;
    posx = board_length/2;
    posy = board_heigth/2;
    x_array[0] = posx;
    y_array[0] = posy;
}
void Snake::init_board(){
    for (int y = 0; y < board_heigth; y++) {
        for (int x = 0; x < board_length; x++) {
            board[0][y] = board[board_length - 1][y] = board[x][0] = board[x][board_heigth - 1] = 1; // we initialise all edges to 1 (integer for the edge of the board)
        }
    }
}
void Snake::draw_board(){
    for (int i = 0; i < board_length; i++){
        for (int j = 0; j < board_heigth; j++){
            std::cout << ANSI_code[board[j][i]];
            //std::cout << board[j][i];
        }
        std::cout << "\n";
    }
}
void Snake::spawn_apple(){
    while (board[apple_posx = rand() % board_length][apple_posy = rand() % board_heigth] != 0){}
    board[apple_posx][apple_posy] = 1;
}
void Snake::move_snake(){
    for(int i = 0; i < snake_length - 1; i++){
        x_array[i] = x_array[i + 1];
        y_array[i] = y_array[i + 1];
    }
}