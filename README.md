# Project_C

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Prerequisites](#prerequisites)
4. [Compilation Steps](#compilation-steps)
5. [Features](#features)
6. [Future Work](#future-work)
7. [Flow of the Code](#flow-of-the-code)
8. [License](#license)


# 3 in 1 Game Project

## Overview
This project is a simple terminal-based game collection with user registration and login functionalities. The project is implemented in C, and it uses custom static libraries to manage the user authentication system.


## Project Structure
- `include/` : Contains the header files.
- `src/` : Contains the source files for user management and utilities.
- `main/` : Contains the main game file.


## Prerequisites

- **GCC Compiler**: Ensure you have GCC installed on your Linux system.
- **Linux Environment**: The project is set up to run on Linux (It can also run on the windows).

## Compilation Steps

To compile and run the project, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/HarshitMalik001/Project_C.git
   ```

2. Navigate to the project directory and run the `run_linux.sh` script:
   ```bash
   cd Project_C
   ./run_linux.sh
   ```

3. Execute the game:
   ```bash
   ./main/game
   ```


## Features

- **User Registration**: Create a new user account with a unique username and password.
- **User Login**: Authenticate existing users to access their game data.
- **Tic-Tac-Toe**: Play Tic-Tac-Toe against the computer with game state saving and loading.
- **Leaderboard**: View a leaderboard displaying user statistics, including wins, losses, and draws.
- **File Handling**: User data and game states are saved to and loaded from files for persistence.

## Future Work

- **Add More Games**: Expand the project by incorporating additional games into the collection.
- **Enhanced AI**: Improve the computer's AI for a more challenging gameplay experience.
- **User Interface**: Develop a more sophisticated user interface for better user interaction.

## Flow Of the Code

![How The Code Is Working](https://github.com/user-attachments/assets/df90c2ff-7477-4ed0-90ea-f6829d3132c2)

## License

This project is open-source and free to use. Feel free to contribute!


