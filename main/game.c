#include <stdio.h>
#include "../include/Mylib.h"

int main()
{
    while(1)
    {
        int usrIndex = Welcome();
        if (usrIndex == -1) return 0;
        UserNode *current = head;

        for(int i = 0; i < usrIndex && current != NULL; i++) {
            current = current->next;
        }
        if(current != NULL) {
            printf("currently logged in %s \n1. log out \n2. Exit\n",current->username);
        }
        
        int option = 2;
        scanf("%d",&option);
        getchar();

        if(option == 2) return 0;
    }
    return 0;
}



