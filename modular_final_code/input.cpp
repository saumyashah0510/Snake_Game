#include "snake_game.h"
using namespace std;

void SnakeGame::Input()
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

        if (((key == 'w' || key == 'W') && (direction != 's' && direction != 'S')) ||
            (key == 's' || key == 'S') && (direction != 'w' && direction != 'W') ||
            (key == 'a' || key == 'A') && (direction != 'd' && direction != 'D') ||
            (key == 'd' || key == 'D') && (direction != 'a' && direction != 'A'))
        {
            direction = key;
        }
    }
}