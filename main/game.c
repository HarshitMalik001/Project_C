#include <stdio.h>
#include "../include/Mylib.h"

int TicTacPlay()
{
    printf("InProgress TicktackPlay\n");
}


int TicTacMenu()
{
    while(1)
    {
        printf("1. Start New Game\n");
        printf("2. LOAD Game \n");
        printf("3. Go back\n");
        printf("Your Choice: ");

        int options = 3;

        if(scanf("%d",&options) != 1)
        {
            while(getchar() != '\n');
            printf("Please Keep the Input In Between 1 - 3 \n");
            options = 4;
        }
        else{
            while(getchar() != '\n');
        }

        switch (options)
        {
        case 1:
            TicTacPlay();
            break;
        case 2:
            printf("In Progress\n");
            break;
        case 3:
            return 0;
            break;
        default:
            printf("Invalid Number\n");
            break;
        }
    }

    return 0;
}

int main()
{
    printf("changes are reflected");
    int islogged = 0;
    int usrIndex = Welcome();
    if (usrIndex == -1) return 0;
    islogged = 1;

    while(1)
    {
        if(!islogged){
            usrIndex = Welcome();
            if (usrIndex == -1) return 0;
            islogged = 1;
        }

        printf("\nWelcome To 3 in 1 Game !!!!! \n");
        printf("Options :- \n");
        printf("1. Tic-Tac-Toe \n");
        printf("2. Logout \n");
        printf("3. Exit \n");
        printf("Your Choice: ");

        int option = 2;

        
        if(scanf("%d",&option) != 1)
        {
            while(getchar() != '\n');
            printf("Please Keep the Input In Between 1 - 3 \n");
            option = 4;
        }
        else{
            while(getchar() != '\n');
        }

        switch(option){
            case 1:
                TicTacMenu();
                break;
            case 2:
                islogged = 0;
                continue;
                break;
            case 3:
                return 0;
                break;
            default:
                printf("\nWrong Choice !!!!!");
                break;
        }
    }
    return 0;
}



