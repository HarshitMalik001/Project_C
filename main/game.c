#include "../include/Mylib.h"
#include <stdio.h>
#include <signal.h>

void handle_sigint(int sig)
{ 
    if(SaveCurrentUser()) printf("\nSaved State Successfully\n");
    printf("\nExited Successfully\n");
    exit(0);
}

int main()
{
    signal(SIGINT, handle_sigint);
    GameMenu();
    return 0;
}