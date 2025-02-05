#include "snake_game.h"

#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random numbers

#if defined(_WIN32) || defined(_WIN64) // Windows-specific includes
#include <conio.h>
#include <windows.h> // For Sleep()
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define sleep_for(milliseconds) Sleep(milliseconds)
#else // Linux/macOS includes
#include <ncurses.h>
#include <unistd.h>                                         // For usleep()
#define sleep_for(milliseconds) usleep(milliseconds * 1000) // Convert ms to us
#endif

using namespace std;

// Constructor and Destructor
SnakeGame::SnakeGame(char difficulty)
{
    head = NULL;
    Initialize(difficulty);
}

SnakeGame::~SnakeGame()
{
    // Clean up the snake's linked list
    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

// Initialize the game state
void SnakeGame::Initialize(char d)
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

    PlaySound(TEXT("sample-15s.wav"), NULL, SND_ASYNC | SND_LOOP);

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


