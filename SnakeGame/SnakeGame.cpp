#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

const int WIDTH = 40;    
const int HEIGHT = 20;  

void gotoxy(int x, int y) {
    COORD coord = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HideCursor() {

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

struct Point {
    int x, y;
};

class SnakeGame {
public:
    Point snake[100];
    int length;
    int direction; // 0: phải, 1: xuống, 2: trái, 3: lên
    Point food;
    bool gameOver;
    int score;
    SnakeGame() {
        length = 3;
        snake[0] = { 10, 10 };
        snake[1] = { 9, 10 };
        snake[2] = { 8, 10 };
        direction = 0;
        gameOver = false;
        score = 0;
        srand(time(0));
        spawnFood();
    }
    //tao snack 
    void spawnFood() {
        bool valid;
        do {
            valid = true;
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
            for (int i = 0; i < length; i++) {
                if (food.x == snake[i].x && food.y == snake[i].y) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);
}

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}



