#include<stdio.h>
#include<conio.h>
#include<string.h>

int login(void);
int choice;
extern char username[]="code2career"; extern char password[]="subhankar";
int login(void)
{
    int Options_after_userauthenticated(int);
    char  id[20], p[20];
    int n=1, x, y;

    do{
         printf("\nusername:");
         scanf("%s", &id);
         fflush(stdout);

         printf("\nPassword:");
         scanf("%s", &p);
         fflush(stdout);

         x=strcmp(id,username);
         y=strcmp(p, password);

         if(x==0 && y==0){
            printf("\nSucessfully Logged In\n");
            printf("1. Set temperature\n");
            printf("2. Get temperature\n");
            printf("Please enter choice: ");
            scanf("%d",&choice);
            Options_after_userauthenticated(choice);
         }else {
           printf("\nWrong Password, try again", 5-n);
            getch();
            n++;}

         if(n>5){
          printf("\nAccess Denied");
          getch();
          }

       }while (n<=5);

}

