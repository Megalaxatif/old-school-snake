#include "snake.h"
bool game_over = false;

int main(){
    system("cls"); // clear the console
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor_info); // the cursor is off for more style :)
    Snake snake(console);
    snake.init_board();
    snake.spawn_apple();
    snake.draw_board();
    snake.move_snake();
    snake.draw_snake_length();
    while (!game_over){
        Sleep(175); // delay
        if (snake.input_handler() == true){ // take the input if it returns true, it means that the game stopped
            game_over = true;
        }
    }
    system("cls");
    cursor_info.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursor_info);
    std::cout << "GAME OVER !";
    return 0;
}
