#include "../include/Mylib.h"
#include <stdio.h>
#include <signal.h>

void handle_sigint(int sig)
{
    printf("Exited Successfully\n");
    SaveCurrentUser();
    exit(0);
}

int main()
{
    signal(SIGINT, handle_sigint);
    GameMenu();
    return 0;
}