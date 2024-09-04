#include "../include/Mylib.h"
#include <stdio.h>

UserNode CurrentUser;

// Defining the filename where to save our user information
const char* ACCOUNT_FILE = "account.dat";

// When we take Input using fgets we get input like this "SomeString\n" 
// because we press enter(\n) we need to define a remove_newline function to remove '\n'

void remove_newline(char *str) {
    size_t len = strlen(str);  
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


void get_password(char *password) {
    int cur = 0;
    char chr;

#ifdef _WIN32
    while ((chr = _getch()) != '\r') {
        if (chr == '\b' && cur > 0) {
            printf("\b \b");
            cur--;
        } else if (chr != '\b') {
            if (cur < CRED_LEN - 1) {
                password[cur++] = chr;
                printf("*");
            }
        }
    }
    password[cur] = '\0';
    printf("\n");
#else
    struct termios old_one, new_one;
    tcgetattr(STDIN_FILENO, &old_one);
    new_one = old_one;
    new_one.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_one);

    while ((chr = getchar()) != '\n' && chr != EOF) 
    {
        if(chr == '!' ) break;
        if (chr == '\b' || chr == 127) 
        {
            if (cur > 0) 
            {
                cur--;
                printf("\b \b");
            }
        } 
        else 
        {
            password[cur++] = chr;
            printf("*");
        }
    }
    password[cur] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &old_one);
    printf("\n");
#endif
}

// EnterCred function to enter Credentials used in both rgstr and login 
int EnterCred(char *username, char *password)
{
    printf("Enter User Name : ");
    fgets(username, CRED_LEN, stdin);
    remove_newline(username);
    printf("Enter Password : ");
    fflush(stdout);  // All the pending output flush 

    get_password(password);
    ClearScreen();
    return 0;
}

int rgstr()
{
    char username[CRED_LEN];
    char password[CRED_LEN];

    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    
    if (file == NULL) {
        printf("\nUnable to open file!!");
        return -1;
    }
    
    fseek(file, 0 , SEEK_SET);

    printf("Register User\n");
    EnterCred(username, password);

    UserNode Dummy;
    while(fread(&Dummy, sizeof(Dummy), 1, file))
    {
        if(strcmp(Dummy.username,username) == 0)
        {
            printf("UserName Already Taken !!!!\n");
            fclose(file);
            return 0;
        }
    }
    
    UserNode new_user;

    strcpy(new_user.username, username);
    strcpy(new_user.pswd, password);

    new_user.Tiktak.player = 0; 
    new_user.Tiktak.computer = 0; 
    new_user.Tiktak.draw = 0;


    fwrite(&new_user, sizeof(new_user), 1, file);
    fclose(file);

    printf("Registeration Succesful !!!!!!\n");
    return 0;
}

// stop
//stop

int login()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return -1;
    }

    char Username[CRED_LEN];
    char Password[CRED_LEN];

    EnterCred(Username, Password);

    UserNode Dummy;
    while(fread(&Dummy, sizeof(Dummy), 1, file)){
        // printf("\n%s %s\n",Dummy.username,Dummy.pswd);
        if(strcmp(Dummy.username, Username) == 0 && strcmp(Dummy.pswd, Password) == 0){

            strcpy(CurrentUser.username, Dummy.username);
            strcpy(CurrentUser.pswd, Dummy.pswd);
            CurrentUser.Tiktak.computer = Dummy.Tiktak.computer;
            CurrentUser.Tiktak.draw = Dummy.Tiktak.draw;
            CurrentUser.Tiktak.player = Dummy.Tiktak.player;

            printf("Successfully Logged in as %s \n",Username);
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return -1;

}

int Welcome()
{
    int user_choice = 3;
    int usrIndex = -1;
    while(1)
    {
        printf("\nWelcome To 3 in 1 Game !!!!! \n");
        printf("Options :- \n");
        printf("1. Register \n");
        printf("2. Login \n");
        printf("3. Exit \n");
        printf("Your Choice: ");

        

        if(scanf("%d", &user_choice) != 1)
        {
            while(getchar() != '\n');
            ClearScreen();
            printf("Please Keep the Input In Between 1 - 3 \n");
            user_choice = 4;
        }
        else{
            while(getchar() != '\n');
            ClearScreen();
        }

        switch (user_choice)
        {
        case 1:
            rgstr();
            break;
        case 2:
            usrIndex = login();
            if(usrIndex >= 0){
                return usrIndex;
            }
            else
            {
                printf("Invalid Details \n");
            }
            break;
        case 3:
            return -1;
            break;
        default:
            printf("Wrong Choice !!!!!\n");
            break;
        }
        user_choice = 4;
    }
}


// To Clear the screen after each operation
int ClearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Functions For tic-tac-toe


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