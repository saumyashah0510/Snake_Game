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
    struct node
    {
        node *next;
        int x, y;

        node()
        {
            this->next = NULL;
        }

        node(int x, int y)
        {
            this->x = x;
            this->y = y;
            this->next = NULL;
        }
    };

    static const int WIDTH = 60;
    static const int HEIGHT = 15;

    node *head;
    int snakeLength;

    int fruitX1, fruitY1;
    int fruitX2, fruitY2;
    int fruitX3, fruitY3;

    int obstacleX1, obstacleY1;
    int obstacleX2, obstacleY2;
    int obstacleX3, obstacleY3;

    int powerupX[4], powerupY[4];
    bool powerupActive[4];
    int powerupTimer[4];
    int powerupDuration[4];

    bool gameOver;
    bool pause;

    char direction; // 'w' = up, 's' = down, 'a' = left, 'd' = right, 'p' = pause

public:
    SnakeGame(char difficulty)
    {
        head = NULL;
        Initialize(difficulty);
    }

    ~SnakeGame()
    {
        // Clean up the snake's linked list
        while (head != NULL)
        {
            node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Initialize(char d)
    {
        gameOver = false;
        direction = 'd';
        snakeLength = 3;

        // Initialize snake
        head = new node(WIDTH / 2, HEIGHT / 2);
        head->next = new node(WIDTH / 2, HEIGHT / 2 + 1);
        head->next->next = new node(WIDTH / 2, HEIGHT / 2 + 2);

        srand(time(0)); // Random positions every run

        // Random fruit positions
        // Generate the first obstacle
        fruitX1 = rand() % (WIDTH - 4) + 2;
        fruitY1 = rand() % (HEIGHT - 4) + 2;
        // Ensure obstacle is not near the snake's starting area
        while (abs(fruitX1 - WIDTH / 2) < 3 && abs(fruitY1 - HEIGHT / 2) < 3)
        {
            fruitX1 = rand() % (WIDTH - 4) + 2;
            fruitY1 = rand() % (HEIGHT - 4) + 2;
        }

        // Generate the second obstacle
        fruitX2 = rand() % (WIDTH - 4) + 2;
        fruitY2 = rand() % (HEIGHT - 4) + 2;
        // Ensure the second obstacle is not near the snake's starting area and also not too close to the first one
        while ((abs(fruitX2 - WIDTH / 2) < 3 && abs(fruitY2 - HEIGHT / 2) < 3) ||
               (abs(fruitX2 - obstacleX1) < 3 && abs(fruitY2 - obstacleY1) < 3))
        {
            fruitX2 = rand() % (WIDTH - 4) + 2;
            fruitY2 = rand() % (HEIGHT - 4) + 2;
        }

        // Generate the third obstacle
        fruitX3 = rand() % (WIDTH - 4) + 2;
        fruitY3 = rand() % (HEIGHT - 4) + 2;
        // Ensure the third obstacle is not near the snake's starting area and not too close to the other obstacles
        while ((abs(fruitX3 - WIDTH / 2) < 3 && abs(fruitY3 - HEIGHT / 2) < 3) ||
               (abs(fruitX3 - obstacleX1) < 3 && abs(fruitY3 - obstacleY1) < 3) ||
               (abs(fruitX3 - obstacleX2) < 3 && abs(fruitY3 - obstacleY2) < 3))
        {
            fruitX3 = rand() % (WIDTH - 4) + 2;
            fruitY3 = rand() % (HEIGHT - 4) + 2;
        }

        // Avoid placing obstacles near the snake
        if (d == '3') // Hard mode with obstacles
        {
            // Generate the first obstacle
            obstacleX1 = rand() % (WIDTH - 4) + 2;
            obstacleY1 = rand() % (HEIGHT - 4) + 2;
            // Ensure obstacle is not near the snake's starting area
            while (abs(obstacleX1 - WIDTH / 2) < 3 && abs(obstacleY1 - HEIGHT / 2) < 3)
            {
                obstacleX1 = rand() % (WIDTH - 4) + 2;
                obstacleY1 = rand() % (HEIGHT - 4) + 2;
            }

            // Generate the second obstacle
            obstacleX2 = rand() % (WIDTH - 4) + 2;
            obstacleY2 = rand() % (HEIGHT - 4) + 2;
            // Ensure the second obstacle is not near the snake's starting area and also not too close to the first one
            while ((abs(obstacleX2 - WIDTH / 2) < 3 && abs(obstacleY2 - HEIGHT / 2) < 3) ||
                   (abs(obstacleX2 - obstacleX1) < 3 && abs(obstacleY2 - obstacleY1) < 3))
            {
                obstacleX2 = rand() % (WIDTH - 4) + 2;
                obstacleY2 = rand() % (HEIGHT - 4) + 2;
            }

            // Generate the third obstacle
            obstacleX3 = rand() % (WIDTH - 4) + 2;
            obstacleY3 = rand() % (HEIGHT - 4) + 2;
            // Ensure the third obstacle is not near the snake's starting area and not too close to the other obstacles
            while ((abs(obstacleX3 - WIDTH / 2) < 3 && abs(obstacleY3 - HEIGHT / 2) < 3) ||
                   (abs(obstacleX3 - obstacleX1) < 3 && abs(obstacleY3 - obstacleY1) < 3) ||
                   (abs(obstacleX3 - obstacleX2) < 3 && abs(obstacleY3 - obstacleY2) < 3))
            {
                obstacleX3 = rand() % (WIDTH - 4) + 2;
                obstacleY3 = rand() % (HEIGHT - 4) + 2;
            }
        }

        // Initialize power-ups
        for (int i = 0; i < 4; i++)
        {
            powerupActive[i] = true;
            powerupTimer[i] = rand() % 16 + 10;
            powerupDuration[i] = 4500;
        }

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
#if defined(_WIN32) || defined(_WIN64)
        clearScreen();
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
                else if (i == head->y && j == head->x)
                {
                    color(10);
                    cout << "X"; // Snake head
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
                else
                {
                    bool isBodyPart = false;
                    node *temp = head->next;
                    while (temp != NULL)
                    {
                        if (temp->x == j && temp->y == i)
                        {
                            color(10);
                            cout << "o"; // Snake body
                            isBodyPart = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!isBodyPart)
                    {
                        // Draw power-ups
                        bool isPowerup = false;
                        if (powerupActive[0] && i == powerupY[0] && j == powerupX[0])
                        {
                            color(14);   // Yellow color for power-ups
                            cout << "+"; // Power-up symbol
                            isPowerup = true;
                            break;
                        }
                        for (int k = 1; k < 4; k++)
                        {
                            if (powerupActive[k] && i == powerupY[k] && j == powerupX[k])
                            {
                                color(14);   // Yellow color for power-ups
                                cout << "-"; // Power-up symbol
                                isPowerup = true;
                                break;
                            }
                        }
                        if (!isPowerup)
                        {
                            cout << " "; // Empty space
                        }
                    }
                }
            }
            cout << endl;
        }
        color(6);
        cout << "Score: " << max(0, snakeLength - 3) << endl;
#else
        clear();
        attron(COLOR_PAIR(5));
        mvprintw(0, 0, "Welcome to Snake Game!!");
        mvprintw(1, 0, "Use 'WASD' to control the snake and 'P' to pause");

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 2, j, "*"); // Border
                    attroff(COLOR_PAIR(3));
                }
                else if (i == head->y && j == head->x)
                {
                    attron(COLOR_PAIR(10));
                    mvprintw(i + 2, j, "O"); // Snake head
                    attroff(COLOR_PAIR(10));
                }
                else if ((i == fruitY1 && j == fruitX1) ||
                         (i == fruitY2 && j == fruitX2) ||
                         (i == fruitY3 && j == fruitX3))
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + 2, j, "@"); // Fruit
                    attroff(COLOR_PAIR(4));
                }
                else if ((i == obstacleY1 && j == obstacleX1) ||
                         (i == obstacleY2 && j == obstacleX2) ||
                         (i == obstacleY3 && j == obstacleX3))
                {
                    attron(COLOR_PAIR(8));
                    mvprintw(i + 2, j, "#"); // Obstacles
                    attroff(COLOR_PAIR(8));
                }
                else
                {
                    bool isBodyPart = false;
                    node *temp = head->next;
                    while (temp != NULL)
                    {
                        if (temp->x == j && temp->y == i)
                        {
                            attron(COLOR_PAIR(10));
                            mvprintw(i + 2, j, "o"); // Snake body
                            attroff(COLOR_PAIR(10));
                            isBodyPart = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!isBodyPart)
                    {
                        // Draw power-ups
                        bool isPowerup = false;
                        for (int k = 0; k < 4; k++)
                        {
                            if (powerupActive[k] && i == powerupY[k] && j == powerupX[k])
                            {
                                attron(COLOR_PAIR(14));  // Yellow color for power-ups
                                mvprintw(i + 2, j, "$"); // Power-up symbol
                                attroff(COLOR_PAIR(14));
                                isPowerup = true;
                                break;
                            }
                        }
                        if (!isPowerup)
                        {
                            mvprintw(i + 2, j, " "); // Empty space
                        }
                    }
                }
            }
        }

        attron(COLOR_PAIR(6));
        mvprintw(HEIGHT + 2, 0, "Score: %d", std::max(0, snakeLength - 3));
        attroff(COLOR_PAIR(6));

        refresh();
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
        int key = getch();
        if (key == ERR)
        {
            return 0;
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
                        if (key == 'p' || key == 'P')
                        {
                            pause = false;
                        }
                    }
                }
            }

            if (direction == ' ' && (key == 'w' || key == 's' || key == 'a' || key == 'd' || key == 'W' || key == 'S' || key == 'A' || key == 'D'))
            {
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
        // Move the snake head
        node *newHead = new node;

        switch (direction)
        {
        case 'w':
        case 'W':
            newHead->y = head->y - 1;
            newHead->x = head->x;
            break;
        case 's':
        case 'S':
            newHead->y = head->y + 1;
            newHead->x = head->x;
            break;
        case 'a':
        case 'A':
            newHead->y = head->y;
            newHead->x = head->x - 1;
            break;
        case 'd':
        case 'D':
            newHead->y = head->y;
            newHead->x = head->x + 1;
            break;
        }
        newHead->next = head;
        head = newHead;

        // Check if the snake eats the fruit
        if ((head->x == fruitX1 && head->y == fruitY1) ||
            (head->x == fruitX2 && head->y == fruitY2) ||
            (head->x == fruitX3 && head->y == fruitY3))
        {
            snakeLength++;

            if (head->x == fruitX1 && head->y == fruitY1)
            {
                fruitX1 = rand() % (WIDTH - 4) + 2;
                fruitY1 = rand() % (HEIGHT - 4) + 2;
            }
            if (head->x == fruitX2 && head->y == fruitY2)
            {
                fruitX2 = rand() % (WIDTH - 4) + 2;
                fruitY2 = rand() % (HEIGHT - 4) + 2;
            }
            if (head->x == fruitX3 && head->y == fruitY3)
            {
                fruitX3 = rand() % (WIDTH - 4) + 2;
                fruitY3 = rand() % (HEIGHT - 4) + 2;
            }
        }
        else
        {
            // Remove the tail
            node *temp = head;
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
        }

        if (snakeLength - 3 < 0)
        {
            cout << "Score negative" << endl;
            gameOver = true;
        }

        if (difficulty == '3')
        {
            if ((head->x == obstacleX1 && head->y == obstacleY1) ||
                (head->x == obstacleX2 && head->y == obstacleY2) ||
                (head->x == obstacleX3 && head->y == obstacleY3))
            {
                gameOver = true;
            }
        }

        // Check collision with walls
        if (head->x == 0 || head->x == WIDTH - 1 || head->y == 0 || head->y == HEIGHT - 1)
            gameOver = true;

        // Check collision with itself
        node *curr = head->next;
        while (curr != NULL)
        {
            if (head->x == curr->x && head->y == curr->y)
            {
                gameOver = true;
                break;
            }
            curr = curr->next;
        }

        // Power-up mechanics
        for (int i = 0; i < 4; i++)
        {
            if (powerupTimer[i] <= 0 && !powerupActive[i])
            {
                powerupX[i] = rand() % (WIDTH - 4) + 2;
                powerupY[i] = rand() % (HEIGHT - 4) + 2;
                powerupActive[i] = true;
                powerupDuration[i] = 4500;
                powerupTimer[i] = rand() % 15 + 10;
            }

            if (powerupActive[i])
            {
                powerupDuration[i] -= 100;
                if (powerupDuration[i] <= 0)
                {
                    powerupActive[i] = false;
                }
            }

            if (powerupActive[i] && head->x == powerupX[i] && head->y == powerupY[i])
            {
                if (i == 0)
                {
                    snakeLength += 3; // Positive power-up
                }
                else
                {
                    snakeLength -= 1; // Negative power-up
                }
                powerupActive[i] = false;
            }
            powerupTimer[i]--;
        }
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
                sleep_for(30);
            }
        }
        color(9);
        cout << "Game Over!" << endl;
        color(7);

        // Restart
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