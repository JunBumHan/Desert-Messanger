#include <stdio.h>
#include <stdlib.h>

#include "show.h"
#include "set.h"

int main(void)
{
    char userInput;

    cleanConsole();
    termsOfService();

    cleanConsole();
    desertMessengerIntro();

    printf("server로 시작하시겠습니까?\n(Y/n) : ");
    scanf(" %c",&userInput);
    if(userInput == 'Y') 
    {
    system("gcc server.c -o server");
    system("./server");
    }
    printf("\nclient로 시작하시겠습니까?");


    

}