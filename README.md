# Snake Game (C++)

## Description:
This is a terminal based snake game implemented in C++. It features different levels and runs on both Windows and Linux\MacOS. 
<br>

## Table of Contents:
- [Features](#features)
- [Installation](#installation)
- [How to play](#how-to-play)
- [License](#License)
- [Programming Concepts Used](#programming-concepts-used)

## Features:

- **Modular**
    - Fully modular code with separate files such as logic.cpp, grid.cpp, etc., each containing functions dedicated to different aspects of the game.

- **OS Independent:**
    - Works on both Windows and Linux\MacOS.
    - Colours and background music are only displayed in Windows.
    - ***It is preferable to run this on Windows.***

- **Multiple Game Modes:**
    - Easy (Slow Speed)
    - Medium (Medium Speed)
    - Fast (Fast Speed and obstacles)

- **Game controls:**
    - `W` - Up
    - `A` - Left
    - `S` - Down
    - `D` - Right
    - `P` - Pause\Resume

- **High Score**
    - A function that displays the maximum score achieved during a session, with the score resetting each time the program is run.   

- **Obstacles:**
    - Randomly placed obstacles (#) (only in hard mode) that end the game if hit.

- **Fruits:**
    - Randomly placed fruits that increases the snake length and score if hit.

- **Power-UP**
    - Randomly placed powerups(+) that increase your score by 3 if eaten.  

- **Bombs** 
    - Randomly placed bombs(-) that decrease your score by 1 if eaten.        

- **Game Over and restart options**    

## Programming concepts used:

1) **Classes** (Encapsulation and Data Hiding)
    - Class used: Snake Game
        - Private members (head, direction, gameOver, etc.) prevent direct access from outside the class.
        - Public methods (Initialize(), Run(), etc.) control access to game logic.

2) **Polymorphism** (Function Overriding & Overloading)   

3) **Linked List** (for the Snake's Body)

4) **Arrays** (for Fruits, Obstacles, and Power-Ups)

5) **Making the code modular**

## Installation

### Pre-requisites
- A C++ compiler (MinGW or MSVC)
- ncurses library (Linux\MacOS only)

<hr>

#### On Windows:
1. **Open a terminal** (Command Prompt or Powershell)
2. **Navigate to the path where file is located**
3. **Compile the code using**:<br>
    ```sh 
    g++ -o snake_game main.cpp logic.cpp snake_game.cpp grid.cpp input.cpp run.cpp utility.cpp -lwinmm
4. **Run the game**
    ```sh
    snake_game.exe   

<hr>

#### On Linux\MacOS:
1. **Install ncurses** if not installed:
    ```sh
    sudo apt-get install libncurses5-dev libncursesw5-dev  # Debian/Ubuntu
    sudo yum install ncurses-devel  # RHEL/Fedora    
2. **Navigate to the path where file is located**
3. **Compile the code:**
    ```sh
    g++ -o snake_game main.cpp logic.cpp snake_game.cpp grid.cpp input.cpp run.cpp utility.cpp -lncurses
4. **Run the game**
    ```sh
    ./snake_game
   
<hr>

## How to play:
1. **Choose a difficulty level** (1.Easy, 2.Medium, 3.Hard)
2. **Control the snake** using `W`, `A`, `S`, `D` (The keys are not case sensitive)
3. **Avoid the walls** (Also the obstacles (#) in hard mode)
4. **Eat fruits** (@ symbol) to grow
5. **Press `P` to pause** the game
6. **If the snake collides** with itself or an obstacle (in Hard mode), the game ends.
7. **If your score goes below 0, the game ends.**
7. **After Game Over, restart or exit**.

## Music Used:
"https://github.com/saumyashah0510/Snake_Game/blob/main/modular_final_code/sample-15s.wav"

## License:
This project is open-source and can be modified as needed.
