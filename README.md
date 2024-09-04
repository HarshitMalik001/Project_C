# Project_C

Going to build a Game in C hope it will be fun to play

# 3 in 1 Game Project

## Overview
This project is a simple terminal-based game collection with user registration and login functionalities. The project is implemented in C, and it uses custom static libraries to manage the user authentication system.

## Project Structure
- `include/` : Contains the header files.
- `src/` : Contains the source files for user management and utilities.
- `main/` : Contains the main game file.

## Prerequisites
- GCC compiler
- Linux environment

## Compilation Steps

### 1. Compile the Library
First, compile the `Mylib.c` file into an object file and then create a static library from it.
```sh
gcc -c src/Mylib.c -o src/MylibExec.o
gcc -c src/Game.c -o src/GameExec.o
ar rcs libMylib.a src/MylibExec.o src/GameExec.o
```
### 2. Compile the Game
Next, compile the main game file (game.c) and link it with the static library to create the final executable.

```sh
gcc main/game.c -L. libMylib.a -o main/mygame
```

### Running the Game

```sh
./main/mygame
```

## Features
- User Registration
- User Login
- Simple terminal-based games
- file handling to save and load user data.


## Future Work
- Add more games to the collection.

## Flow Of the Code
![How The Code Is Working](https://github.com/user-attachments/assets/fa7f74d0-2d80-4edf-9866-dd3f08c20a93)
 
