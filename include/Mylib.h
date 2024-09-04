#ifndef MYLIB_H
#define MYLIB_H

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
#endif

// Defining the filename where to save our user information
#define ACCOUNT_FILE  "account.dat"

#define CRED_LEN 40

// typedef 

typedef struct UserNode {
    char username[CRED_LEN];
    char pswd[CRED_LEN];
    struct {
        int player;
        int computer;
        int draw;
        char turn;
        char Board[3][3];
    } Tiktak;
} UserNode;

// User
void remove_newline(char *str);
int EnterCred(char *username, char *password);
int rgstr();
int login();
int Welcome();
void get_password(char *password);
int ClearScreen();

// Tiktactoe
void printBoard(char Board[3][3]);
int checkWin(char Board[3][3], char curPlayer);
int checkDraw(char Board[3][3]);
int isValid(char Board[3][3], int row, int col);
void PlayerTurn(char Board[3][3], char curPlayer);
int TicTacPlay();
int leaderBoard();
int TicTacMenu();
int SaveCurrentUser();
int GameMenu();


#endif
