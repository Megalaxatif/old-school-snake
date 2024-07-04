#include "snake.h"

int main(){
    system("cls"); // clear the console
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor_info); // the cursor is off for more style :)
    Snake snake(console);

    while (snake.get_game_status() != GAME_STATUS::GAME_QUIT){
        Sleep(175); // delay
        snake.input_handler(); // take the input and move the snake
        if(snake.get_game_status() == GAME_STATUS::GAME_OVER) snake.game_over(); // basically, it restart the game if we lose
        
    }   
    system("cls"); // clear the console
    cursor_info.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursor_info);
    std::cout << "GAME OVER !";
    return 0;
}
