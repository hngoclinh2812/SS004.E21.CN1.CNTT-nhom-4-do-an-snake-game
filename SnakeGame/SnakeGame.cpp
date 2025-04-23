#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

void gotoxy(int x, int y)
{
    COORD coord = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

struct Point
{
    int x, y;
};

class SnakeGame
{
public:
    Point snake[100];
    int length;
    int direction; // 0: phải, 1: xuống, 2: trái, 3: lên
    Point food;
    bool gameOver;
    int score;
    int speed;

    int lichsu_diem[100];
    int so_lan_choi;

    SnakeGame()
    {
        so_lan_choi = 0;
        HideCursor();
        srand(time(0));
        resetGame();
    }

    void resetGame()
    {
        length = 3;
        snake[0] = { 10, 10 };
        snake[1] = { 9, 10 };
        snake[2] = { 8, 10 };
        direction = 0;
        gameOver = false;
        score = 0;
        speed = 150;
        spawnFood();
    }

    void spawnFood()
    {
        bool valid;
        do
        {
            valid = true;
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
            for (int i = 0; i < length; i++)
            {
                if (food.x == snake[i].x && food.y == snake[i].y)
                {
                    valid = false;
                    break;
                }
            }
        }
        while (!valid);
    }

    void Input()
    {
        if (_kbhit())
        {
            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                if (key == 75 && direction != 0) direction = 2;
                if (key == 77 && direction != 2) direction = 0;
                if (key == 72 && direction != 1) direction = 3;
                if (key == 80 && direction != 3) direction = 1;
            }
        }
    }

    void Update()
    {
        for (int i = length - 1; i > 0; i--)
            snake[i] = snake[i - 1];

        switch (direction)
        {
        case 0:
            snake[0].x++;
            break;
        case 1:
            snake[0].y++;
            break;
        case 2:
            snake[0].x--;
            break;
        case 3:
            snake[0].y--;
            break;
        }

        if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 || snake[0].y <= 0 || snake[0].y >= HEIGHT - 1)
            gameOver = true;

        for (int i = 1; i < length; i++)
        {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                gameOver = true;
        }

        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            length++;
            score += 10;
            if (speed > 50)
                speed -= 10;
            spawnFood();
        }
    }

    void Render()
    {
        gotoxy(0, 0);
        for (int i = 0; i < WIDTH; i++) cout << "#";
        cout << "\n";
        for (int i = 1; i < HEIGHT - 1; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (j == 0 || j == WIDTH - 1)
                    cout << "#";
                else
                    cout << " ";
            }
            cout << "\n";
        }
        for (int i = 0; i < WIDTH; i++) cout << "#";

        for (int i = 0; i < length; i++)
        {
            gotoxy(snake[i].x, snake[i].y);
            cout << (i == 0 ? "O" : "o");
        }

        gotoxy(food.x, food.y);
        cout << "*";

        gotoxy(0, HEIGHT);
        cout << "Score: " << score;
    }

    void showHistory()
    {
        cout << "\nLich su diem so:\n";
        for (int i = 0; i < so_lan_choi; i++)
        {
            cout << "- Lan " << i + 1 << ": " << lichsu_diem[i] << endl;
        }
    }

    void Run()
    {
        char choi_tiep;
        do
        {
            resetGame();
            while (!gameOver)
            {
                Input();
                Update();
                Render();
                Sleep(speed);
            }

            lichsu_diem[so_lan_choi++] = score;

            gotoxy(0, HEIGHT + 2);
            cout << "Game Over! Diem cua ban: " << score << endl;

            showHistory();

            cout << "\nBan co muon choi lai? (y/n): ";
            cin >> choi_tiep;

        }
        while (choi_tiep == 'y' || choi_tiep == 'Y');

        gotoxy(0, HEIGHT + 10);
        cout << "Cam on ban da choi!\n";
    }
};

int main()
{
    SnakeGame game;
    game.Run();
    return 0;
}
