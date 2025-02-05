#include "snake_game.h"
using namespace std;

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

// Main game loop
void SnakeGame::Run(char d)
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
    cout << "Your final score was " << max(0, snakeLength - 3) << endl;
    cout << "High score: " << high_score << endl;
    color(7);

    // Restart
    char restart;
    color(2);
    do
    {
        PlaySound(0, 0, 0);
        cout << "Do you want to play again?" << endl
             << "Press 'y' to play again and 'n' to exit" << endl;
        cin >> restart;
        if (restart == 'y' || restart == 'Y')
        {
            PlaySound(TEXT("sample-15s.wav"), NULL, SND_ASYNC | SND_LOOP);
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