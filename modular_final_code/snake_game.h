#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream>

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
    int high_score = 0;
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
    char direction;

public:
    SnakeGame(char difficulty);
    ~SnakeGame();
    void Initialize(char difficulty);
    void Grid();
    char getKeyPress();
    void Input();
    void Logic(char difficulty);
    void Run(char difficulty);
    void clearScreen();
    void color(int c);
    void refreshScreen();
    void cleanup();
    void PlaySound(const char *soundFile);
};

#endif // SNAKE_GAME_H
