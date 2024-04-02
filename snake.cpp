#include "snake.h"

const char* ANSI_code[4] = {"\033[37m  \033[0m", "\033[37;47m@@\033[0m", "\033[31m[]\033[0m", "\033[32;1m[]\033[0m"}; // empty space, border, fruit, snake

Snake::Snake() : board{ 0 } {
    snake_length = 0;
    posx = board_length/2;
    posy = board_heigth/2;
    x_array[0] = posx;
    y_array[0] = posy;
    apple_posx = 0;
    apple_posy = 0;
    board_length = 10;
    board_heigth = 15;
    srand((unsigned)time(NULL));
}
void Snake::init_board(){
    for (int y = 0; y < board_heigth; y++) {
        for (int x = 0; x < board_length; x++) {
            board[0][y] = board[board_length - 1][y] = board[x][0] = board[x][board_heigth - 1] = (int)INDEX::BORDER;
        }
    }
}
void Snake::draw_board(){
    for (int i = 0; i < board_heigth; i++){
        for (int j = 0; j < board_length; j++){
            std::cout << ANSI_code[board[j][i]];
            //std::cout << board[j][i];
        }
        std::cout << "\n";
    }
}
void Snake::spawn_apple(){
    while (board[apple_posx = rand() % board_length][apple_posy = rand() % board_heigth] != (int)INDEX::EMPTY_SPACE){}
    board[apple_posx][apple_posy] = (int)INDEX::FRUIT;
}
void Snake::input_handler(){
     if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
     }
     if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
     }
     if (GetAsyncKeyState(VK_UP) & 0x8000) {
     }
     if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
     }
}
void Snake::move_snake(int dirx, int diry){
    if (board[posx + dirx][posy + diry] == (int)INDEX::EMPTY_SPACE || board[posx + dirx][posy + diry] == (int)INDEX::FRUIT){ // the snake moves only if there is an empty space or a fruit right in front of it
        // we set the new value of posx and posy
        posx = posx + dirx;
        posy = posy + diry;
        // we set the new position of the head
        x_array[snake_length] = posx;
        y_array[snake_length] = posy;
    }
    // we move the array
    for(int i = 0; i < snake_length - 1; i++){
        x_array[i] = x_array[i + 1];
        y_array[i] = y_array[i + 1];
    }
}