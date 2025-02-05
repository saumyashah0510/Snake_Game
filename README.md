# Snake Game (C++)

## Description:
This is a terminal based snake game implemented in C++. It features different levels and runs on both Windows and Linux\MacOS. 
<br>

## Team: Silicon Syndicates
202401472 - Saumya Shah <br>
202404038 - Manav Shah  <br>
202404030 - Pranshu Vaghani <br>
202404017 - Krishh Agrawal <br>

## Table of Contents:
- [Features](#features)
- [Installation](#installation)
- [How to play](#how-to-play)
- [License](#License)

## Features:

- **OS Independent:**
    - Works on both Windows and Linux\MacOS.

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

- **Obstacles:**
    - Randomly placed obstacles (#) (only in hard mode) that end the game if hit.

- **Fruits:**
    - Randomly placed fruits that increases the snake length and score if hit.

- **Power-UP**
    - Randomly placed powerups(+) that increase your score by 3 if eaten.  

- **Bombs** 
    - Randomly placed bombs(-) that decrease your score by 1 if eaten.        

- **Game Over and restart options**    

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
    g++ my_version.cpp -o my_version.exe
4. **Run the game**
    ```sh
    my_version.exe    

<hr>

#### On Linux\MacOS:
1. **Install ncurses** if not installed:
    ```sh
    sudo apt-get install libncurses5-dev libncursesw5-dev  # Debian/Ubuntu
    sudo yum install ncurses-devel  # RHEL/Fedora    
2. **Navigate to the path where file is located**
3. **Compile the code:**
    ```sh
    g++my_version.cpp -omy_version -lncurses
4. **Run the game**
    ```sh
    ./my_version
   
<hr>

## How to play:
1. **Choose a difficulty level** (1.Easy, 2.Medium, 3.Hard)
2. **Control the snake** using `W`, `A`, `S`, `D` (The keys are not case sensitive)
3. **Avoid the walls** (Also the obstacles (#) in hard mode)
4. **Eat fruits** (@ symbol) to grow
5. **Press `P` to pause** the game
6. **If the snake collides** with itself or an obstacle (in Hard mode), the game ends.
7. **After Game Over, restart or exit**.

## License:
This project is open-source and can be modified as needed.