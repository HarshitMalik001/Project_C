#include <stdio.h>
#include "../include/Mylib.h"
#include <string.h>
#define CRED_LEN 30

typedef struct 
{
    char username[CRED_LEN];
    char pswd[CRED_LEN];
} USER_INFO;

int max_usr = 10;
int usr_count = 0;

USER_INFO User_Info[10];


int Welcome()
{
    int user_choice = 3;
    int l = -1;
    while(1)
    {
        printf("Welcome To 3 in 1 Game !!!!! \n");
        printf("Options :- \n");
        printf("1. Register \n");
        printf("2. Login \n");
        printf("3. Exit \n");

        scanf("%d", &user_choice);

        getchar();
        switch (user_choice)
        {
        case 1:
            rgstr();
            break;
        case 2:
            l = login();
            if(l >= 0)
            {
                printf("Welcome User s \n");
                return l;
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

        user_choice = 3;
    }
}

int main()
{
    while(1)
    {
        int a = Welcome();
        if (a == -1) return 0;
        printf("currently logged in %s 1. log out \n2. Exit\n",User_Info[a].username);
        int option = 2;
        scanf("%d",&option);

        if(option == 2) return 0;
    }
    return 0;
}

int EnterCred(char *username, char *password)
{
    printf("Enter User Name : ");
    fgets(username, CRED_LEN, stdin);
    printf("%s",username);
    printf("Enter User Password : ");
    fgets(password, CRED_LEN, stdin);
    return 0;
}

int rgstr()
{
    if(usr_count == max_usr) return -1;

    printf("Register User\n");
    EnterCred(User_Info[usr_count].username, User_Info[usr_count].pswd );
    printf("Registeration Succesful\n");
    usr_count++;
    return 0;
}

int login()
{
    char Username[30];
    char Password[30];
    EnterCred(Username, Password);

    for (int i = 0; i < usr_count; i++) {
        if (strcmp(Username, User_Info[i].username) == 0 && strcmp(Password, User_Info[i].pswd) == 0) {
            return i;
        }
    }

    return -1;

}
