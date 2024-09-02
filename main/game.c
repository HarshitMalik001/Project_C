#include <stdio.h>
#include "../include/Mylib.h"


void printBoard(char Board[3][3])
{
    printf("\n\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf(" %c ",Board[i][j]);
            if(j != 2)
            {
                printf("|");
            }
        }
        if(i != 2)
        {
            printf("\n---+---+---\n");
        }
    }
    printf("\n\n");
}

int checkWin(char Board[3][3], char curPlayer)
{
    for(int i = 0; i < 3; i++)
    {        
        if(Board[i][0]==curPlayer && Board[i][1]==curPlayer && Board[i][2]==curPlayer) return 1;
        if(Board[0][i]==curPlayer && Board[1][i]==curPlayer && Board[2][i]==curPlayer) return 1;
    }
    if(Board[0][0]==curPlayer && Board[1][1]==curPlayer && Board[2][2]==curPlayer) return 1;
    if(Board[2][0]==curPlayer && Board[1][1]==curPlayer && Board[0][2]==curPlayer) return 1;

    return  0;
}

int checkDraw(char Board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(Board[i][j] == ' ') return 0;
        }
    }

    return 1;
}


int TicTacPlay()
{
    while(1){
        char Board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        
        printBoard(Board);
        ClearScreen();
    }
}


int TicTacMenu()
{

    while(1)
    {
        printf("\n   Tic-Tac-Toe   \n");
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
            ClearScreen();
            printf("Please Keep the Input In Between 1 - 3 \n");
            option = 4;
        }

        else
        {
            while(getchar() != '\n');
            ClearScreen();
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



