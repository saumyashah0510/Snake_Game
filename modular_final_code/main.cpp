#include "snake_game.h"

int main()
{
    char difficulty;
    do
    {
        std::cout << "Choose Difficulty: " << std::endl;
        std::cout << "1. Easy" << std::endl
                  << "2. Medium" << std::endl
                  << "3. Hard" << std::endl;
        std::cin >> difficulty;
        std::cin.ignore(); // Clear the input buffer

        if (difficulty != '1' && difficulty != '2' && difficulty != '3')
        {
            std::cout << "Invalid input! Please enter a valid difficulty." << std::endl;
        }
    } while (difficulty != '1' && difficulty != '2' && difficulty != '3');

    SnakeGame game(difficulty);
    game.Run(difficulty);

    return 0;
}
