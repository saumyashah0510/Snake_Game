#include "snake_game.h"

using namespace std;

void SnakeGame ::Logic(char d)
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

    if (d == '3')
    {
        if ((head->x == obstacleX1 && head->y == obstacleY1) ||
            (head->x == obstacleX2 && head->y == obstacleY2) ||
            (head->x == obstacleX3 && head->y == obstacleY3))
        {
            gameOver = true;
        }
    }

    // check highscore
    if (snakeLength - 3 > high_score)
    {
        high_score = snakeLength - 3;
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