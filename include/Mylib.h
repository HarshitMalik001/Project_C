#ifndef MYLIB_H
#define MYLIB_H

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define CRED_LEN 40

typedef struct {
  int player;
  int computer;
  int draw;
} Score;

typedef struct UserNode {
    char username[CRED_LEN];
    char pswd[CRED_LEN];
    Score Tiktak;
} UserNode;

// extern UserNode;

void remove_newline(char *str);
int EnterCred(char *username, char *password);
int rgstr();
int login(UserNode *user);
int Welcome(UserNode *user);
int ClearScreen();

#endif
