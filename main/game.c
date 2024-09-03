#include <stdio.h>
#include "../include/Mylib.h"
#include <time.h>
#include <stdlib.h>

typedef struct {
  int player;
  int computer;
  int draw;
} Score;
Score score = {.player = 0, .computer = 0, .draw = 0};

void printBoard(char Board[3][3])
{
    ClearScreen();
    printf("Your History : \n");
    printf("Player Won %d, Computer Won %d, Draw %d\n",score.player,score.computer,score.draw);
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

int isValid(char Board[3][3], int row, int col)
{
    if(row < 1 || row > 3 || col < 1 || col > 3 || Board[row - 1][col - 1] != ' ') return 0;
    return 1;
}

void PlayerTurn(char Board[3][3], char curPlayer)
{
    int row,col;
    int bool1;
    int bool2;
    do {
        printf("Player %c Turn\n",curPlayer);
        bool1 = scanf("%d",&row);
        bool2 = scanf("%d",&col);
    }
    while(!isValid(Board, row , col));
    printf("%d %d \n",row, col);
    Board[row - 1][col - 1] = curPlayer;

}


int TicTacPlay()
{
    char Board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    srand(time(NULL));
    char cur_player = rand() % 2 == 0 ? 'O' : 'X';

    printBoard(Board);

    while(1){
        PlayerTurn(Board, cur_player);
        printBoard(Board);
        if(checkWin(Board,cur_player)){
            printBoard(Board);
            printf("Congratulation player %c Won !!\n",cur_player);
            cur_player == 'O' ? score.player++ : score.computer++; 
            break;
        }
        else if(checkDraw(Board)){
            printBoard(Board);
            printf("It's a Draw !!!\n");
            score.draw++;
            break;
        }
        cur_player = cur_player == 'O'? 'X' : 'O';
    }
    printf("Enter 1 if You Want To Play Again : ");
    int playAgain;
    scanf("%d",&playAgain);
    if(playAgain == 1) return 1;
    return 0;
}


int TicTacMenu()
{

    while(1)
    {
        printf(" Welcome To Tic-Tac-Toe !!!! \n");
        printf("\n1. Start New Game\n");
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
            while(TicTacPlay() == 1);
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
    ClearScreen();
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


