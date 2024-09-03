#include "../include/Mylib.h"
#include <stdio.h>


// Defining the filename where to save our user information
const char* ACCOUNT_FILE = "account.dat";


// When we take Input using fgets we get input like this "SomeString\n" 
// because we press enter(\n) we need to define a remove_newline function to remove '\n'

void remove_newline(char *str) {
    /* Can use unsigned int to store the size of str but I saw on many website that size_t is prefered over unsigned int */

    size_t len = strlen(str);  
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// EnterCred function to enter Credentials used in both rgstr and login 
int EnterCred(char *username, char *password)
{
    printf("Enter User Name : ");
    fgets(username, CRED_LEN, stdin);
    remove_newline(username);
    printf("Enter Password : ");
    fflush(stdout);  // All the pending output flush 

    // Changing Terminal setting so that the password is hidden when we type
    struct termios old_one, new_one;
    tcgetattr(STDIN_FILENO, &old_one);
    new_one = old_one;
    new_one.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_one);

    int cur = 0;
    char chr;

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


int login(UserNode *User)
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

            strcpy(User->username, Dummy.username);
            strcpy(User->pswd, Dummy.pswd);
            User->Tiktak.computer = Dummy.Tiktak.computer;
            User->Tiktak.draw = Dummy.Tiktak.draw;
            User->Tiktak.player = Dummy.Tiktak.player;
            
            printf("Successfully Logged in as %s \n",Username);
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return -1;

}




int Welcome(UserNode *User)
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
            usrIndex = login(User);
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