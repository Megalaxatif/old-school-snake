#include "snake.h"

#define DRAW_CALL(c, t, x, y) {\
    SetConsoleTextAttribute(console, text_attribute[c]);\
    goto_(x, y);\
    std::cout << t;\
    goto_(x, y + 1);\
    std::cout << t;\
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);\
    }

unsigned int text_attribute[] = {
    BACKGROUND_GREEN | BACKGROUND_INTENSITY,// empty space
    BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,// border
    FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_INTENSITY,  // fruit
    BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_INTENSITY // snake
};

Snake::Snake(HANDLE console_) : board{ 0 } {
    console = console_;
    game_status = GAME_STATUS::GAME_PLAYING;
    is_key_enter_pressed = false;
    snake_length = 1;
    // initial snake coordinates
    posx = board_length / 2;
    posy = board_heigth / 2;
    dirx = 0;
    diry = 0;
    x_array[0] = posx;
    y_array[0] = posy;
    apple_posx = 0;
    apple_posy = 0;
    ath_posx = (board_posx + board_length)*4 + 6;
    ath_posy = 0;
    srand((unsigned)time(NULL));

    init_board();
    spawn_apple();
    draw_board();
    move_snake();
    draw_snake_length();
}

void Snake::game_over(){
    // reset the snake length
    snake_length = 1;
    // initial snake coordinates
    posx = board_length / 2;
    posy = board_heigth / 2;
    // reset the coordinates arrays
    for(int i = 0; i < snake_length; i++){
        x_array[i] = y_array[i] = 0;
    } 
    x_array[0] = posx;
    y_array[0] = posy;
    dirx = 0;
    diry = 0;

    system("cls");
    init_board();
    spawn_apple();
    draw_board();
    move_snake();
    draw_snake_length();

    game_status = GAME_STATUS::GAME_PLAYING;
}
GAME_STATUS Snake::get_game_status(){
    return game_status;
}

void Snake::init_board(){
    for (int y = 0; y < board_heigth; y++) {
        for (int x = 0; x < board_length; x++) {
            board[x][y] = (int)INDEX::EMPTY_SPACE;
            board[0][y] = board[board_length - 1][y] = board[x][0] = board[x][board_heigth - 1] = (int)INDEX::BORDER;
        }
    }
}
void Snake::draw_board(){
    for (int i = 0; i < board_heigth; i++){
        for (int j = 0; j < board_length; j++){
            goto_(board_posx + j, board_posy + i);
            DRAW_CALL(board[j][i], "    ", (board_posx + j)*4, (board_posy + i)*2);
        }
    }
}
void Snake::draw_snake_length(){
    goto_(ath_posx, ath_posy);
    std::cout << "SNAKE LENGTH: " << snake_length;

}
void Snake::goto_(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}
void Snake::spawn_apple(){
    while (board[apple_posx = rand() % board_length][apple_posy = rand() % board_heigth] != (int)INDEX::EMPTY_SPACE){}
    board[apple_posx][apple_posy] = (int)INDEX::FRUIT;
    DRAW_CALL((int)INDEX::FRUIT, "    ", (board_posx + apple_posx)*4, (board_posy + apple_posy)*2);
}
void Snake::input_handler(){
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_BACK) & 0x8000)) { // quit the game by clicking control + delete
        game_status = GAME_STATUS::GAME_QUIT;
    }

    if (game_status != GAME_STATUS::GAME_PAUSE){
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && dirx != -1) {
            dirx = 1; diry = 0;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && dirx != 1) {
            dirx = -1; diry = 0;
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000 && diry != 1) {
            dirx = 0; diry = -1;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && diry != -1) {
            dirx = 0; diry = 1;
        }
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000 && is_key_enter_pressed == false) { // pause the game by clicking enter
            is_key_enter_pressed = true;
            game_status = GAME_STATUS::GAME_PAUSE;
        }
        else if (!(GetAsyncKeyState(VK_RETURN) & 0x8000)){
            is_key_enter_pressed = false;
        }
        if (!move_snake()) game_status = GAME_STATUS::GAME_OVER; // stop the game if a collision happened
    }

    else {
        if (!(GetAsyncKeyState(VK_RETURN) & 0x8000)){
            is_key_enter_pressed = false;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && is_key_enter_pressed == false){
            is_key_enter_pressed = true;
            game_status = GAME_STATUS::GAME_PLAYING;
        }
    }
}
bool Snake::move_snake(){
    if (board[posx + dirx][posy + diry] == (int)INDEX::EMPTY_SPACE || board[posx + dirx][posy + diry] == (int)INDEX::FRUIT){ // the snake moves only if there is an empty space or a fruit right in front of it
        board[x_array[snake_length - 1]][y_array[snake_length - 1]] = (int)INDEX::EMPTY_SPACE; // delete the tail of the snake before any change in the board
        DRAW_CALL((int)INDEX::EMPTY_SPACE, "    ", (board_posx + x_array[snake_length - 1])*4, (board_posy + y_array[snake_length - 1])*2); // draw deleted tail
        // in case of collision with a fruit
        if(board[posx + dirx][posy + diry] == (int)INDEX::FRUIT){
            // creating a new segment of the snake which is equal to the segment before it, so when it'll move, the new segment's value will not change but the one after it will
            x_array[snake_length] = x_array[snake_length - 1];
            y_array[snake_length] = y_array[snake_length - 1];
            snake_length ++;
            board[x_array[snake_length - 1]][y_array[snake_length - 1]] = (int)INDEX::SNAKE; // set the new tail of the snake in the board
            Sleep(200); // short delay
            draw_snake_length(); // counter
            spawn_apple();
        }
        // we move the array
        for(int i = 0; i < snake_length - 1; i++){
            x_array[snake_length - i - 1] = x_array[snake_length - i - 2]; // reminder: the array is read upside down (from the end to the start)
            y_array[snake_length - i - 1] = y_array[snake_length - i - 2];
        }
        // we set the new value of posx and posy (head)
        posx = posx + dirx;
        posy = posy + diry;
        // we set the new position of the head
        x_array[0] = posx;
        y_array[0] = posy;
        board[x_array[0]][y_array[0]] = (int)INDEX::SNAKE; // head of the snake
        DRAW_CALL((int)INDEX::SNAKE, "    ", (board_posx + x_array[0])*4, (board_posy + y_array[0])*2); // draw head
        DRAW_CALL((int)INDEX::SNAKE, "    ", (board_posx + x_array[snake_length - 1])*4, (board_posy + y_array[snake_length - 1])*2); // draw new tail
        return true;
    }
    else if (dirx == 0 && diry == 0) return true; // if the snake is immobile
    else return false; // so the snake touched a border or itself, it's game over
}