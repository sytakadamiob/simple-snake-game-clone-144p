#include <ctime> // at top for time()
#include <cstdlib>      // rand
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Global variables
bool gameOver;
const int HEIGHT = 20;
const int WIDTH = 25;
int x, y, appleX, appleY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Function prototypes 
int kbhit();
int getch();
void printTitle();
void setUp();
void draw();
void userInput();
void gameLogic();

int main()
{
    srand(time(0));     // Initialize random seed
    setUp();
    while (!gameOver)
    {
        draw();
        userInput();
        gameLogic();
        printTitle();
        usleep(120000); // ~120 ms per tick (adjust 60–200 ms to taste)
    }
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void printTitle()
{
    cout << "--  Simple Snake Game 144p  --" << endl;
}

void setUp()
{
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    appleX = rand() % (WIDTH - 2) + 1;  // Range: 1 to WIDTH-2
    appleY = rand() % (HEIGHT - 2) + 1; // Range: 1 to HEIGHT-2
    score = 0;
    nTail = 0;
}

void draw()
{
    system("clear");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // Draw borders
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == appleY && j == appleX)
                cout << "*"; // Apple
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void userInput()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
        default:
            break;
        }
    }
}

void gameLogic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case LEFT:
        x--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    if (x > WIDTH - 2 || x < 1 || y > HEIGHT - 2 || y < 1)
        gameOver = true;

    for (int i = 1; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == appleX && y == appleY)
    {
        score += 1;
        appleX = rand() % (WIDTH - 2) + 1;      
        appleY = rand() % (HEIGHT - 2) + 1;
        nTail++;
    }
}