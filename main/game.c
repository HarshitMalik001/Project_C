#include <stdio.h>


int Welcome()
{
    int user_choice = 3;
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
            //register();
            break;
        case 2:
            //int l = login();
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
