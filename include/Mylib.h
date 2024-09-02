#ifndef MYLIB_H
#define MYLIB_H

#define CRED_LEN 40

typedef struct UserNode {
    char username[CRED_LEN];
    char pswd[CRED_LEN];
} UserNode;

extern UserNode *head;
extern int usr_count;

void remove_newline(char *str);
int EnterCred(char *username, char *password);
int rgstr();
int login();
int Welcome();
int ClearScreen();

#endif
