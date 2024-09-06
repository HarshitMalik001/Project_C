
// Functions For tic-tac-toe
#include "../include/Mylib.h"
#include <stdio.h>

extern UserNode CurrentUser;
//  printing the game Board

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


// check if curPlayer have Won
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

// check if it's a draw
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

// check if the move is valid
int isValid(char Board[3][3], int row, int col)
{
    if(row < 1 || row > 3 || col < 1 || col > 3 || Board[row - 1][col - 1] != ' ') return 0;
    return 1;
}

// Player Turn 
void PlayerTurn(char Board[3][3], char curPlayer)
{
    if (curPlayer == 'X')
    {
        printf("Computer's Turn\n");
        ComputerTurn(Board, curPlayer);
        return;
    }
    
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

// Computer Turn
void ComputerTurn(char Board[3][3], char curPlayer)
{

    printf("Computer is Thinking");
    fflush(stdout);

    for(int i = 1; i < 20; i++)
    {
        usleep(100000);
        printf(".");
        fflush(stdout);
        
        if(i%3 == 0){
            usleep(100000);
            printf("\b\b\b   \b\b\b");
            fflush(stdout);
        }
    }
    printf("!\n");
    fflush(stdout);


    // check if computer can win in next move
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(Board[i][j] == ' '){
                Board[i][j] = curPlayer;
                if( checkWin(Board, curPlayer) ) return;
                Board[i][j] = ' ';
            }
        }
    }

    // check if computer can lose in next move so computer can block
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(Board[i][j] == ' '){
                char ff = curPlayer == 'X' ? 'O' :'X';
                Board[i][j] = ff;
                if( checkWin(Board, ff) ){
                    Board[i][j] = curPlayer;
                    return;
                }
                Board[i][j] = ' ';
            }
            
        }
    }


    // 
    srand(time(NULL));

    // To lower the diffuclty we made it so computer always Does'nt Play the best move

    if(rand() % 2 == 0){
        // Random Move by computer
        int countEmpty = 0;
        
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(Board[i][j] == ' ') countEmpty++;
            }
        }

        int randMove = rand() % countEmpty;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(Board[i][j] == ' ')
                {
                    if(randMove == 0)
                    {
                        Board[i][j] = curPlayer;
                        return;
                    }
                    randMove--;
                }
            }
        }
    }
    else{
        // Best Possible move by computer
        if(Board[1][1] == ' ') Board[1][1] = curPlayer;
        else if(Board[0][0] == ' ') Board[0][0] = curPlayer;
        else if(Board[0][2] == ' ') Board[0][2] = curPlayer;
        else if(Board[2][0] == ' ') Board[2][0] = curPlayer;
        else if(Board[2][2] == ' ') Board[2][2] = curPlayer;
        else if(Board[0][1] == ' ') Board[0][1] = curPlayer;
        else if(Board[1][0] == ' ') Board[1][0] = curPlayer;
        else if(Board[1][2] == ' ') Board[1][2] = curPlayer;
        else if(Board[2][1] == ' ') Board[2][1] = curPlayer;
        return;
    }

    return;
}

// Game Entry Point

int TicTacPlay()
{
    char cur_player;
    srand(time(NULL));
    if(CurrentUser.Tiktak.turn == ' ') cur_player = rand() % 2 == 0 ? 'O' : 'X';
    else cur_player = CurrentUser.Tiktak.turn;

    printBoard(CurrentUser.Tiktak.Board);

    while(1){
        PlayerTurn(CurrentUser.Tiktak.Board, cur_player);
        printBoard(CurrentUser.Tiktak.Board);
        if(checkWin(CurrentUser.Tiktak.Board,cur_player)){
            cur_player == 'O' ? CurrentUser.Tiktak.player++ : CurrentUser.Tiktak.computer++; 
            printBoard(CurrentUser.Tiktak.Board);
            printf("Congratulation player %c Won !!\n",cur_player);
            break;
        }
        else if(checkDraw(CurrentUser.Tiktak.Board)){
            CurrentUser.Tiktak.draw++;
            printBoard(CurrentUser.Tiktak.Board);
            printf("It's a Draw !!!\n");
            break;
        }
        cur_player = cur_player == 'O'? 'X' : 'O';
        CurrentUser.Tiktak.turn = cur_player; 
    }

    printf("Enter 1 if You Want To Play Again : ");
    int playAgain;
    scanf("%d",&playAgain);
    if(playAgain == 1) return 1;
    else SaveCurrentUser();
    return 0;
}


// Compare Users for LeaderBoard
int compareUsers(const void *a, const void *b) {
    UserNode *userA = (UserNode *)a;
    UserNode *userB = (UserNode *)b;

    if (userB->Tiktak.player != userA->Tiktak.player)
        return userB->Tiktak.player - userA->Tiktak.player;

    if (userB->Tiktak.computer != userA->Tiktak.computer)
        return  userA->Tiktak.computer - userB->Tiktak.computer;

    return userB->Tiktak.draw - userA->Tiktak.draw;
}

// LeaderBoard

int leaderBoard()
{
    ClearScreen();
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return -1;
    }

    fseek(file, 0 , SEEK_END);

    long filesize = ftell(file);
    int noOfUser = filesize / sizeof(UserNode);
     
    UserNode *listOfUsers = (UserNode *) malloc(sizeof(UserNode) * noOfUser);

    if(listOfUsers == NULL)
    {
        printf("Error in Memory Allocating\n");
        fclose(file);
        return -1;
    }

    fseek(file , 0, SEEK_SET);
    fread(listOfUsers, sizeof(UserNode), noOfUser, file);
    qsort(listOfUsers, noOfUser, sizeof(UserNode), compareUsers);

    printf("Leaderboard\n");
    printf("Position | Player Wins | Computer Wins | Draws | Username\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < noOfUser; i++) {
        printf("%8d | %11d | %13d | %5d | %s",i + 1, listOfUsers[i].Tiktak.player, listOfUsers[i].Tiktak.computer, listOfUsers[i].Tiktak.draw, listOfUsers[i].username);
        if (strcmp(listOfUsers[i].username, CurrentUser.username) == 0) {
            printf(" <--- You are here");
        }
        printf("\n");
    }

    free(listOfUsers);
    fclose(file);
    printf("\n");
    return 0;
}

//  Empty the array 
void clearBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            CurrentUser.Tiktak.Board[i][j] = ' ';
        }
    } 
    CurrentUser.Tiktak.turn = ' ';
}


//  Menu for Tictactoe
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
            printf("Please Do Not Enter A Non-Integer Value \n");
            options = 5;
        }
        else{
            while(getchar() != '\n');
            
        }

        switch (options)
        {
        case 1:
            printf("All The Previous Data will be deleted Enter 1 to confirm : ");
            int n;
            if(scanf("%d",&n) != 1)
            {
                while(getchar() != '\n');
                n = 0;
            }
            
            if(n != 1)
            {
                ClearScreen();
                continue;
            };

            do
            {
                printf("Play Again Called\n");
                clearBoard();
            } while (TicTacPlay() == 1);
            break;
        case 2:
            if(checkWin(CurrentUser.Tiktak.Board, 'X')|| checkWin(CurrentUser.Tiktak.Board, 'O') || checkDraw(CurrentUser.Tiktak.Board))
            {
                clearBoard();
            }
            while(TicTacPlay() == 1)
            {
                clearBoard();
            }
            break;
        case 3:
            leaderBoard();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("Please Keep the Input In Between 1 - 4 \n");
            break;
        }
    }
    return 0;
}


int SnakePlay()
{
    ClearScreen();
    printf("InProgress \n");
    return 0;
}

// Game Menu For Snake & Fruits (Currently Incomplete); 
int SnakeMenu()
{
    while(1)
    {
        printf(" Welcome To Snake & Fruits !!!! \n");
        printf("\n1. Start New Game\n");
        printf("2. LOAD Game \n");
        printf("3. LeaderBoard \n");
        printf("4. Go back\n");
        printf("Your Choice: ");

        int options = 4;

        if(scanf("%d",&options) != 1)
        {
            while(getchar() != '\n');
            printf("Please Do Not Enter A Non-Integer Value \n");
            options = 5;
        }
        else{
            while(getchar() != '\n');
        }

        switch (options)
        {
        case 1:
            printf("All The Previous Data will be deleted Enter 1 to confirm : ");
            int n;
            if(scanf("%d",&n) != 1)
            {
                while(getchar() != '\n');
                n = 0;
            }
            
            if(n != 1)
            {
                ClearScreen();
                continue;
            };

            while (SnakePlay() == 1);
            break;

        case 2:
            ClearScreen();
            printf("In Progress\n");
            break;
        case 3:
            // leaderBoard();
            ClearScreen();
            printf("In Progress\n");
            break;
        case 4:
            return 0;
            break;
        default:
            printf("Please Keep the Input In Between 1 - 3 \n");
            break;
        }
    }
    return 0;
}



//  Save the state of current User
int SaveCurrentUser()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return 0;
    }

    // Overwriting the previous data of User with new one
    UserNode Dummy;
    while(fread(&Dummy, sizeof(Dummy), 1, file))
    {
        if(strcmp(Dummy.username, CurrentUser.username) == 0)
        {
            fseek(file, -sizeof(Dummy), SEEK_CUR);
            fwrite(&CurrentUser, sizeof(CurrentUser), 1, file);
            fclose(file);
            return 1;
        }
    }

    printf("User Not Found\n");
    fclose(file);
    return 0;
}


// Menu for Games
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
        printf("2. Snake&Fruit \n");
        printf("3. Logout \n");
        printf("4. Exit \n");
        printf("Your Choice: ");

        int option = 5;

        if(scanf("%d",&option) != 1)
        {
            while(getchar() != '\n');
            ClearScreen();
            printf("Please Do Not Enter any Non-Integer Input \n");
            option = 5;
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
                SnakeMenu();
                break;
            case 3:
                islogged = 0;
                SaveCurrentUser();
                continue;
                break;
            case 4:
                SaveCurrentUser();
                return 0;
                break;
            default:
                printf("Please Keep the Input In Between 1 - 4 \n");
                break;
        }
    }
    return 0;
}