#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random numbers

#if defined(_WIN32) || defined(_WIN64) // Windows-specific includes
#include <conio.h>
#include <windows.h> // For Sleep()
#define sleep_for(milliseconds) Sleep(milliseconds)
#else // Linux/macOS includes
#include <ncurses.h>
#include <unistd.h>                                         // For usleep()
#define sleep_for(milliseconds) usleep(milliseconds * 1000) // Convert ms to us
#endif

using namespace std;

class SnakeGame
{
private:
    static const int WIDTH = 60;
    static const int HEIGHT = 15;

    int snake_X[450], snake_Y[450]; // Arrays to hold snake body positions
    int snakeLength;

    int fruitX1, fruitY1;
    int fruitX2, fruitY2;
    int fruitX3, fruitY3;

    int obstacleX1, obstacleY1;
    int obstacleX2, obstacleY2;
    int obstacleX3, obstacleY3;

    int powerup1X, powerup1Y;
    int powerup2X, powerup2Y;
    int powerup3X, powerup3Y;
    int powerup4X, powerup4Y;
    bool powerup1 = false;
    bool powerup2 = false;
    bool powerup3 = false;
    bool powerup4 = false;
    int powerup1_timer = 0;
    int powerup2_timer = 0;
    int powerup3_timer = 0;
    int powerup4_timer = 0;
    int powerup1_duration = 4500;
    int powerup2_duration = 4600;
    int powerup3_duration = 4750;
    int powerup4_duration = 5000;

    bool gameOver;
    bool pause = false;

    char direction; // 'w' = up, 's' = down, 'a' = left, 'd' = right, 'p' = pause

public:
    SnakeGame(char difficulty)
    {
        Initialize(difficulty);
    }

    void Initialize(char d)
    {
        gameOver = false;
        direction = ' ';
        snakeLength = 1;
        snake_X[0] = WIDTH / 2;
        snake_Y[0] = HEIGHT / 2;

        srand(time(0)); // random positions every run

        // Random fruit position
        fruitX1 = rand() % (WIDTH - 4) + 2;
        fruitY1 = rand() % (HEIGHT - 4) + 2;

        fruitX2 = rand() % (WIDTH - 4) + 2;
        fruitY2 = rand() % (HEIGHT - 4) + 2;

        fruitX3 = rand() % (WIDTH - 4) + 2;
        fruitY3 = rand() % (HEIGHT - 4) + 2;

        if (d == '3')
        {
            obstacleX1 = rand() % (WIDTH - 4) + 2;
            obstacleY1 = rand() % (HEIGHT - 4) + 2;

            obstacleX2 = rand() % (WIDTH - 4) + 2;
            obstacleY2 = rand() % (HEIGHT - 4) + 2;

            obstacleX3 = rand() % (WIDTH - 4) + 2;
            obstacleY3 = rand() % (HEIGHT - 4) + 2;
        }

        // reset power up
        powerup1 = true;
        powerup2 = true;
        powerup3 = true;
        powerup4 = true;
        powerup1_timer = rand() % 16 + 30;
        powerup2_timer = rand() % 16 + 10;
        powerup3_timer = rand() % 16 + 12;
        powerup4_timer = rand() % 16 + 14;

#if defined(_WIN32) || defined(_WIN64)
        // No additional setup required for Windows
#else
        initscr();
        noecho();
        curs_set(0);
        timeout(1);
        nodelay(stdscr, TRUE);
#endif
    }

    void clearScreen()
    {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        clear();
#endif
    }

    void color(int c)
    {
#if defined(_WIN32) || defined(_WIN64)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
        attron(COLOR_PAIR(c));
#endif
    }

    void Grid()
    {
#if defined(_WIN32) || defined(_WIN64) // For Windows
        clearScreen();                 // Clear the screen on Windows
        color(5);
        cout << "Welcome to snake game!!" << endl;
        cout << "Use 'wasd' for controlling the snake and 'p' to pause" << endl;

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                {
                    color(3);
                    cout << "*"; // Border
                }
                else if (i == snake_Y[0] && j == snake_X[0])
                {
                    color(10);
                    cout << "O"; // Snake head
                }
                else if ((i == fruitY1 && j == fruitX1) ||
                         (i == fruitY2 && j == fruitX2) ||
                         (i == fruitY3 && j == fruitX3))
                {
                    color(4);
                    cout << "@"; // Fruit
                }
                else if ((i == obstacleY1 && j == obstacleX1) ||
                         (i == obstacleY2 && j == obstacleX2) ||
                         (i == obstacleY3 && j == obstacleX3))
                {
                    color(3);
                    cout << "*"; // Obstacles
                }
                else if (powerup1 == true && i == powerup1Y && j == powerup1X)
                {
                    color(6);
                    cout << "+";
                }
                else if (powerup2 == true && i == powerup2Y && j == powerup2X)
                {
                    color(6);
                    cout << "-";
                }
                else if (powerup3 == true && i == powerup3Y && j == powerup3X)
                {
                    color(6);
                    cout << "-";
                }

                else if (powerup4 == true && i == powerup4Y && j == powerup4X)
                {
                    color(6);
                    cout << "-";
                }
                else
                {
                    bool isBodyPart = false;
                    for (int k = 1; k < snakeLength; k++)
                    {
                        if (snake_X[k] == j && snake_Y[k] == i)
                        {
                            color(10);
                            cout << "O"; // Snake body
                            isBodyPart = true;
                            break;
                        }
                    }
                    if (!isBodyPart)
                        cout << " ";
                }
            }
            cout << endl;
        }
        color(6);
        cout << "Score: " << max(0, snakeLength - 1) << endl;

#else // For Linux (Using ncurses)
        clear(); // Clear screen in Linux
        color(5);
        mvprintw(0, 0, "Welcome to snake game!!");
        mvprintw(1, 0, "Use 'wasd' for controlling the snake and 'p' to pause");

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                {
                    color(3);
                    mvprintw(i + 2, j, "*"); // Border
                }
                else if (i == snake_Y[0] && j == snake_X[0])
                {
                    color(10);
                    mvprintw(i + 2, j, "X"); // Snake head
                }
                else if ((i == fruitY1 && j == fruitX1) ||
                         (i == fruitY2 && j == fruitX2) ||
                         (i == fruitY3 && j == fruitX3))
                {
                    color(4);
                    mvprintw(i + 2, j, "@"); // Fruit
                }
                else if ((i == obstacleY1 && j == obstacleX1) ||
                         (i == obstacleY2 && j == obstacleX2) ||
                         (i == obstacleY3 && j == obstacleX3))
                {
                    color(8);
                    mvprintw(i + 2, j, "#"); // Obstacles
                }
                else
                {
                    bool isBodyPart = false;
                    for (int k = 1; k < snakeLength; k++)
                    {
                        if (snake_X[k] == j && snake_Y[k] == i)
                        {
                            color(10);
                            mvprintw(i + 2, j, "o"); // Snake body
                            isBodyPart = true;
                            break;
                        }
                    }
                    if (!isBodyPart)
                        mvprintw(i + 2, j, " ");
                }
            }
        }

        color(6);
        mvprintw(HEIGHT + 2, 0, "Score: %d", max(0, snakeLength - 1));

        refresh(); // Refresh screen after drawing everything
#endif
    }

    char getKeyPress()
    {
#if defined(_WIN32) || defined(_WIN64)
        if (_kbhit())
        {
            return _getch();
        }
#else
        int key = getch(); // Get the key press
        if (key == ERR)
        {
            return 0; // No key pressed
        }
        return key;
#endif
        return 0;
    }

    void Input()
    {

        char key = getKeyPress();
        if (key)
        {
            if (key == 'p' || key == 'P')
            {
                pause = !pause;
                if (pause)
                {
                    color(6);
                    cout << "Game paused. Press 'p' to resume" << endl;
                    while (pause)
                    {
                        key = getKeyPress();
                        {
                            if (key == 'p' || key == 'P')
                            {
                                pause = false;
                            }
                        }
                    }
                }
            }

            if (direction == ' ' && (key == 'w' || key == 's' || key == 'a' || key == 'd' || key == 'W' || key == 'S' || key == 'A' || key == 'D'))
            {
                // Start moving once the first key is pressed
                direction = key;
            }
            else if (((key == 'w' || key == 'W') && (direction != 's' && direction != 'S')) ||
                     (key == 's' || key == 'S') && (direction != 'w' && direction != 'W') ||
                     (key == 'a' || key == 'A') && (direction != 'd' && direction != 'D') ||
                     (key == 'd' || key == 'D') && (direction != 'a' && direction != 'A'))
            {
                direction = key;
            }
        }
    }

    void Logic(char difficulty)
    {
        // Move the snake body
        for (int i = snakeLength; i > 0; i--)
        {
            snake_X[i] = snake_X[i - 1];
            snake_Y[i] = snake_Y[i - 1];
        }

        // Move the snake head
        switch (direction)
        {
        case 'w':
            snake_Y[0]--;
            break;
        case 'W':
            snake_Y[0]--;
            break;
        case 's':
            snake_Y[0]++;
            break;
        case 'S':
            snake_Y[0]++;
            break;
        case 'a':
            snake_X[0]--;
            break;
        case 'A':
            snake_X[0]--;
            break;
        case 'd':
            snake_X[0]++;
            break;
        case 'D':
            snake_X[0]++;
            break;
        }

        if (snakeLength <= 0)
        {
            gameOver = true;
        }

        // Check collision with walls
        if (snake_X[0] == 0 || snake_X[0] == WIDTH - 1 || snake_Y[0] == 0 || snake_Y[0] == HEIGHT - 1)
            gameOver = true;

        // Check collision with itself
        for (int i = 1; i < snakeLength; i++)
        {
            if (snake_X[0] == snake_X[i] && snake_Y[0] == snake_Y[i])
                gameOver = true;
        }

        // Check if the snake eats the fruit
        if ((snake_X[0] == fruitX1 && snake_Y[0] == fruitY1) ||
            (snake_X[0] == fruitX2 && snake_Y[0] == fruitY2) ||
            (snake_X[0] == fruitX3 && snake_Y[0] == fruitY3))
        {
            snakeLength++;
            if (snake_X[0] == fruitX1 && snake_Y[0] == fruitY1)
            {
                fruitX1 = rand() % (WIDTH - 4) + 2;
                fruitY1 = rand() % (HEIGHT - 4) + 2;
            }
            if (snake_X[0] == fruitX2 && snake_Y[0] == fruitY2)
            {
                fruitX2 = rand() % (WIDTH - 4) + 2;
                fruitY2 = rand() % (HEIGHT - 4) + 2;
            }
            if (snake_X[0] == fruitX3 && snake_Y[0] == fruitY3)
            {
                fruitX3 = rand() % (WIDTH - 4) + 2;
                fruitY3 = rand() % (HEIGHT - 4) + 2;
            }
        }

        if (difficulty == '3')
        {
            if ((snake_X[0] == obstacleX1 && snake_Y[0] == obstacleY1) ||
                (snake_X[0] == obstacleX2 && snake_Y[0] == obstacleY2) ||
                (snake_X[0] == obstacleX3 && snake_Y[0] == obstacleY3))
            {
                gameOver = true;
            }
        }

        // Power-up mechanics
        if (powerup1_timer <= 0 && powerup1 == false)
        {
            powerup1X = rand() % (WIDTH - 4) + 2;
            powerup1Y = rand() % (HEIGHT - 4) + 2;
            powerup1 = true;
            powerup1_duration = 4500;
            powerup1_timer = rand() % 15 + 30; // Reset spawn timer
        }
        if (powerup2_timer <= 0 && powerup2 == false)
        {
            powerup2X = rand() % (WIDTH - 4) + 2;
            powerup2Y = rand() % (HEIGHT - 4) + 2;
            powerup2 = true;
            powerup2_duration = 4500;
            powerup2_timer = rand() % 15 + 10; // Reset spawn timer
        }
        if (powerup3_timer <= 0 && powerup3 == false)
        {
            powerup3X = rand() % (WIDTH - 4) + 2;
            powerup3Y = rand() % (HEIGHT - 4) + 2;
            powerup3 = true;
            powerup3_duration = 4500;
            powerup3_timer = rand() % 15 + 12; // Reset spawn timer
        }
        if (powerup4_timer <= 0 && powerup4 == false)
        {
            powerup4X = rand() % (WIDTH - 4) + 2;
            powerup4Y = rand() % (HEIGHT - 4) + 2;
            powerup4 = true;
            powerup4_duration = 4500;
            powerup4_timer = rand() % 15 + 14; // Reset spawn timer
        }

        if (powerup1 == true)
        {
            powerup1_duration = powerup1_duration - 100;
            if (powerup1_duration <= 0)
            {
                powerup1 = false; // Remove power-up from screen
            }
        }
        if (powerup2 == true)
        {
            powerup2_duration = powerup2_duration - 100;
            if (powerup2_duration <= 0)
            {
                powerup2 = false; // Remove power-up from screen
            }
        }
        if (powerup3 == true)
        {
            powerup3_duration = powerup3_duration - 100;
            if (powerup3_duration <= 0)
            {
                powerup3 = false; // Remove power-up from screen
            }
        }
        if (powerup4 == true)
        {
            powerup4_duration = powerup4_duration - 100;
            if (powerup4_duration <= 0)
            {
                powerup4 = false; // Remove power-up from screen
            }
        }

        if (powerup1 == true && snake_X[0] == powerup1X && snake_Y[0] == powerup1Y)
        {
            snakeLength += 3; // Increase score by 3
            powerup1 = false; // Remove power-up
        }
        powerup1_timer--;
        if (powerup2 == true && snake_X[0] == powerup2X && snake_Y[0] == powerup2Y)
        {
            snakeLength -= 1;
            powerup2 = false; // Remove power-up
        }
        powerup2_timer--;
        if (powerup3 == true && snake_X[0] == powerup3X && snake_Y[0] == powerup3Y)
        {
            snakeLength -= 1;
            powerup3 = false; // Remove power-up
        }
        powerup3_timer--;
        if (powerup4 == true && snake_X[0] == powerup4X && snake_Y[0] == powerup4Y)
        {
            snakeLength -= 1;
            powerup4 = false; // Remove power-up
        }
        powerup4_timer--;
    }

    void Run(char d)
    {
        while (!gameOver)
        {
            if (!pause)
            {
                Grid();
                Input();
                Logic(d);
            }

            if (d == '1')
            {
                sleep_for(200);
            }
            else if (d == '2')
            {
                sleep_for(100);
            }
            else if (d == '3')
            {
                sleep_for(20);
            }
        }
        color(9);
        cout << "Game Over!" << endl;
        color(7);

        // restart
        char restart;
        color(2);
        do
        {
            cout << "Do you want to play again?" << endl
                 << "Press 'y' to play again and 'n' to exit" << endl;
            cin >> restart;
            if (restart == 'y' || restart == 'Y')
            {
                Initialize(d);
                Run(d);
            }
            else if (restart == 'n' || restart == 'N')
            {
                cout << "Thanks for playing.";
            }
            else
            {
                cout << "Please enter correct input" << endl;
            }
        } while (restart != 'y' && restart != 'n' && restart != 'Y' && restart != 'N');

#if !defined(_WIN32) && !defined(_WIN64)
        endwin();
#endif
    }
};

int main()
{
    char difficulty;

    do
    {
        cout << "Choose Difficulty: " << endl;
        cout << "1. Easy" << endl
             << "2. Medium" << endl
             << "3. Hard" << endl;
        cin >> difficulty;
        cin.ignore(); // Clear the input buffer

        if (difficulty != '1' && difficulty != '2' && difficulty != '3')
        {
            cout << "Invalid input! Please enter a valid difficulty." << endl;
        }
    } while (difficulty != '1' && difficulty != '2' && difficulty != '3');

    SnakeGame game(difficulty);
    game.Run(difficulty);

    return 0;
}