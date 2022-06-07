#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "show.h"

int main(void)
{
    system("clear");

    char userInput[100]; // User input
    if(!terms_of_service())
    {
        printf("종료합니다\n");
        exit(1);
    }

    system("clera");

    desertMessengerIntro();

    puts("");

    printf("컴파일할 제체를 선택해주세요?\n");
    printf("server : client> ");

    scanf("%s",userInput);

        if(!strcmp(userInput, "server"))
        {
            printf("server를 컴파일 했습니다.\n");

            system("sudo rm server");

            for(int i = 0; i < 50000000; ++i); //Busy Waiting

            system("sudo gcc server.c -o server");
            
            for(int i = 0; i < 50000000; ++i); //Busy Waiting
           
            exit(1);
        }

        if(!strcmp(userInput, "client"))
        {
            printf("client를 컴파일 했습니다.\n");

            system("rm client");

            for(int i = 0; i < 50000000; ++i); //Busy Waiting

            system("sudo gcc client.c -o client");

            for(int i = 0; i < 50000000; ++i); //Busy Waiting
          
            exit(1);
        }

    printf("입력하진 정보가 알맞지 않습니다.\n");
    exit(1);
    
}