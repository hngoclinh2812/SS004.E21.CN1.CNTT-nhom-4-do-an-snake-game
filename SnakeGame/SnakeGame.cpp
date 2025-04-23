#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
// Kích thước khung trò chơi
const int WIDTH = 40;    // Chiều ngang
const int HEIGHT = 20;   // Chiều dọc

// ======= HÀM DI CHUYỂN CON TRỎ TRONG CONSOLE =======
void gotoxy(int x, int y) {
    COORD coord = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// ======= HÀM ẨN CON TRỎ CHUỘT TRONG CONSOLE =======
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
}

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}



