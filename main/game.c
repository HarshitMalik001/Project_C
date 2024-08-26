#include <stdio.h>
#include "../include/Mylib.h"

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
            }
            else
            {
                printf("Invalid Details \n");
            }
            break;
        case 3:
            return 0;
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
    Welcome();
    return 0;
}


int rgstr()
{
    printf("Register called\n");
    return 0;
}

int login()
{
    printf("login called\n");
    return 0;
}