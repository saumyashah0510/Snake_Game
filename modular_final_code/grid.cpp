#include "snake_game.h"
using namespace std;

void SnakeGame ::Grid()
{
#if defined(_WIN32) || defined(_WIN64)
    clearScreen();
    color(5);
    cout << "Welcome to snake game!!" << endl;
    cout << "Use 'wasd' for controlling the snake and 'p' to pause" << endl;
    cout << " '@' are fruits and eating them will increase the length of the snake and score by 1." << endl;
    cout << " '+' are powerups and eating them will increase your score by 3 points. " << endl;
    cout << " '-' are bombs and eating them will decrease your score by 1 point. " << endl;
    cout << "You lose either when you hit walls/obstacles or when your score goes below zero." << endl; 

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
                            // Draw power-up symbol
                            if (k == 0)
                            {
                                // Draw + for the first power-up
                                attron(COLOR_PAIR(POWERUP_COLOR));
                                mvprintw(i + 2, j, "+");
                                attroff(COLOR_PAIR(POWERUP_COLOR));
                            }
                            else
                            {
                                // Draw - for the other power-ups
                                attron(COLOR_PAIR(POWERUP_COLOR));
                                mvprintw(i + 2, j, "-");
                                attroff(COLOR_PAIR(POWERUP_COLOR));
                            }
                            isPowerup = true;
                            break;
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
