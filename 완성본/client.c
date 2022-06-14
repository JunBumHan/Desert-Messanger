/*/////////////////
client 입니다.
*//////////////////

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "show.h"
#include "socketSet.h"

int main(int argc, char * argv[])
{
    system("clear"); //console claer
 
    if(argc != 4) // 올바른 사용법인지 확인
    {
        printf("Usage : %s <IP> <PORT> <NAME>\n", argv[0]);
        exit(1);
    }
    /*
        argv[0] : ./exe
        argv[1] : IP
        argv[2] : PORT
        argv[3] : clntName
    */


    char message[BUF_SIZE]; //전송 및 수신 데이터
    char servUserName[BUF_SIZE]; // 클라이언트측 이름

    int sock; // 소켓 


    sock = clnt_connect(AF_INET, argv[1], atoi(argv[2]));
    
    switch(sock)
    {
        case SOCKET_ERROR: error_handling("socket() error");
        case CONNECT_ERROR: error_handling("connect() error");
    }
   
        write(sock, argv[3], sizeof(argv[3])); // Server에게 Client가 사용하는 이름 송신
        sleep(0.5);
        read(sock, servUserName, sizeof(servUserName)); // Client에서 사용하는 이름 Server에게 수신
     

    sleep(0.5);
    bool isInput = false;
    spectatMode();
    
    while(true)
    {
        while(isInput == INPUTMODE)
        {
            sleep(0.5);

            printf("\n%s> ",argv[3]);
            fgets(message, BUF_SIZE, stdin); 
            message[strlen(message)-1] = '\0';


                if(strcmp(message, "pass") == 0) // pass 이라면
                {
                    isInput = false;
                    spectatMode();
                    write(sock, "pass", 5);
                    break;
                }

                if(strcmp(message, "help") == 0) //help 이라면
                {
                    _help();
                    continue;
                }

                if(strcmp(message, "quit") == 0) //quit 이라면
                {
                    printf("종료합니다.\n");
                    write(sock, "quit", 5);
                    close(sock);
                    exit(1);
                }

            write(sock, message,sizeof(message)); // clnt에게 입력한 데이터 전송
        }

        while(isInput == SPECTATMODE)
        {
            
            sleep(0.5);
            read(sock, message,sizeof(message));

                if(strcmp(message, "pass") == 0)
                {
                    isInput = true;
                    inputMode();
                    break;
                }

                if(strcmp(message, "quit") == 0)
                {
                    printf("%s님이 나가셨습니다",servUserName);
                    exit(1);
                }

            printf("\n%s> %s\n",servUserName, message);

        }
    }

}




