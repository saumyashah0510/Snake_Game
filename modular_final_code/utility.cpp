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

char SnakeGame::getKeyPress()
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

void SnakeGame::clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    clear();
#endif
}

void SnakeGame::color(int c)
{
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
    attron(COLOR_PAIR(c));
#endif
}

