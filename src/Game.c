
// Functions For tic-tac-toe
#include "../include/Mylib.h"
#include <stdio.h>

extern UserNode CurrentUser;


void printBoard(char Board[3][3])
{
    ClearScreen();
    printf("Your History : \n");
    printf("Player Won %d, Computer Won %d, Draw %d\n",CurrentUser.Tiktak.player, CurrentUser.Tiktak.computer, CurrentUser.Tiktak.draw);
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
    do {
        printf("Player %c Turn\n",curPlayer);

        if(scanf("%d",&row) != 1)
        {
            while (getchar() != '\n');
            printf("Please Keep the Input In Between 1 - 3 \n");
            continue;
        }
         if(scanf("%d",&col) != 1)
        {
            while (getchar() != '\n');
            printf("Please Keep the Input In Between 1 - 3 \n");
            continue;
        }
    }
    while(!isValid(Board, row , col));

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
            cur_player == 'O' ? CurrentUser.Tiktak.player++ : CurrentUser.Tiktak.computer++; 
            break;
        }
        else if(checkDraw(Board)){
            printBoard(Board);
            printf("It's a Draw !!!\n");
            CurrentUser.Tiktak.draw++;
            break;
        }
        cur_player = cur_player == 'O'? 'X' : 'O';
    }
    printf("Enter 1 if You Want To Play Again : ");
    int playAgain;
    scanf("%d",&playAgain);
    if(playAgain == 1) return 1;
    else SaveCurrentUser();
    return 0;
}


int leaderBoard()
{
    ClearScreen();
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return -1;
    }
    printf("List of All Players \n");
    printf("Win Lose Draw UserName\n");
    UserNode Dummy;
    while(fread(&Dummy, sizeof(Dummy), 1, file))
    {
        printf(" %d   %d    %d    %s",Dummy.Tiktak.player, Dummy.Tiktak.computer, Dummy.Tiktak.draw, Dummy.username);
        if(strcmp(Dummy.username,CurrentUser.username) == 0)
        {
            printf(" <--- You are here");
        }
        printf("\n");
    }
    fclose(file);
    printf("\n");
    return 0;
}


int TicTacMenu()
{
    while(1)
    {
        printf(" Welcome To Tic-Tac-Toe !!!! \n");
        printf("\n1. Start New Game\n");
        printf("2. LOAD Game \n");
        printf("3. LeaderBoard \n");
        printf("4. Go back\n");
        printf("Your Choice: ");

        int options = 4;

        if(scanf("%d",&options) != 1)
        {
            while(getchar() != '\n');
            printf("Please Keep the Input In Between 1 - 3 \n");
            options = 5;
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
            leaderBoard();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("Invalid Number\n");
            break;
        }
    }
    return 0;
}


int SaveCurrentUser()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return -1;
    }

    UserNode Dummy;
    while(fread(&Dummy, sizeof(Dummy), 1, file))
    {
        if(strcmp(Dummy.username,CurrentUser.username) == 0)
        {
            fseek(file, -sizeof(Dummy), SEEK_CUR);
            fwrite(&CurrentUser, sizeof(CurrentUser), 1, file);
            fclose(file);
            return 0;
        }
    }
    printf("User Not Found\n");
    fclose(file);
    return 0;
}

int GameMenu()
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

        printf("Currently Logged in as %s\n" , CurrentUser.username);
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
                SaveCurrentUser();
                continue;
                break;
            case 3:
                SaveCurrentUser();
                return 0;
                break;
            default:
                printf("\nWrong Choice !!!!!");
                break;
        }
    }
    return 0;
}