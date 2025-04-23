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

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 'x') Huong = 1;
        }
        system("cls");
        r.Ve();
        r.DiChuyen(Huong);
        r.AnMoi();

        Sleep(300);
    }

    return 0;
}



