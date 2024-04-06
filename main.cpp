#include "snake.h"
bool game_over = false;

int main(){
    system("cls"); // clear the console
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    Snake snake(console);
    snake.init_board();
    snake.spawn_apple();
    snake.move_snake();
    snake.draw_board();
    while (!game_over){
        Sleep(200); // delay
        if (snake.input_handler() == true){ // take the input if it returns true, it means that the game stopped
            game_over = true;
        }
    }
    system("cls");
    std::cout << "GAME OVER !";
    return 0;
}
