
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;

int tailX[100], tailY[100];
int tailLength = 0;

int x, y, fruitX, fruitY, score;

enum eDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirection dir;

void setup();
void draw();
void input();
void logic();

void setup() {
    gameOver = false;
    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
    tailLength = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void draw() {
    COORD coord = { 0, 0 };

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (j == 0)
                cout << "#";

            if (i == y && j == x) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "*";
            }
            else {
                bool printTail = false;

                for (int a = 0; a < tailLength; a++) {
                    if (tailX[a] == j && tailY[a] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }

                if (!printTail)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {

            case 'a':
                dir = LEFT;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'r':
                gameOver = true;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score++;
        tailLength++;

        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main() {
    srand(time(0));

    while (true) {
        char op;

        setup();

        while (!gameOver) {
            draw();
            input();
            logic();

            Sleep(50);
        }

        system("cls");

        cout << "\n\n\n\n\t\t\tGAME OVER";
        cout << "\n\t\t\tSCORE: " << score;
        cout << "\n\n";

        cout << "press r to restart\t\t\tpress e to exit\n\n";
        cout << "\n\t\t\t>";

        cin >> op;

        switch (op) {
            case 'r':
                break;

            case 'e':
                exit(1);

            default:
                cout << "Invalid input" << endl;
        }

        system("cls");
    }

    return 0;
}
