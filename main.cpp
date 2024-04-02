#include "snake.h"

int main(){
    Snake snake;
    snake.init_board();
    snake.spawn_apple();
    snake.draw_board();

    return 0;
}
