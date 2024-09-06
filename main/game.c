#include "../include/Mylib.h"
#include <stdio.h>
#include <signal.h>

// Handling when user press ctrl + c 
void handle_sigint(int sig)
{ 
    // Saving state of current user when ctrl + c is pressed
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