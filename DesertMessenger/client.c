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
    system("clear"); // console claer
 
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

    // Variable declaration
    int sock; // Socket 

    char message[BUF_SIZE];      // Message
    char servUserName[BUF_SIZE]; // Server User Name
    // // // // // //


    sock = clnt_connect(AF_INET, argv[1], atoi(argv[2])); // connect 까지 수행한 뒤 파일디스리터 저장
    
    switch(sock) // Error 검사
    {
        case SOCKET_ERROR: error_handling("socket() error");   // SOCKET_ERROR 
        case CONNECT_ERROR: error_handling("connect() error"); // CONNECT_ERROR 
    }
   
        write(sock, argv[3], sizeof(argv[3]));          // Server에게 Client가 사용하는 이름 송신
        sleep(BUSY_WAITING); 
        read(sock, servUserName, sizeof(servUserName)); // Client에서 사용하는 이름 Server에게 수신
     

    sleep(BUSY_WAITING);

    bool isInput = false; // isInput - False
    spectatMode(); // Spectat mode
    
    while(true)  // Infinite loop
    {
        while(isInput == INPUTMODE) // Input mode 
        {
            sleep(BUSY_WAITING);

            printf("\n%s> ",argv[3]); // clntName 출력
            fgets(message, BUF_SIZE, stdin); // 입력 
            message[strlen(message)-1] = 'NULL'; // 개행(enter) 지워주기


                if(strcmp(message, "pass") == 0) // pass 이라면
                {
                    isInput = false;
                    spectatMode();
                    write(sock, "pass", 5);
                    break;
                }

                if(strcmp(message, "help") == 0) // help 이라면
                {
                    _help();
                    continue;
                }

                if(strcmp(message, "quit") == 0) // quit 이라면
                {
                    printf("종료합니다.\n");
                    write(sock, "quit", 5);
                    close(sock);
                    exit(1);
                }
        write(sock, message,sizeof(message)); // server에게 입력한 데이터 전송

        } // while(isInput == INPUTMODE)

        while(isInput == SPECTATMODE) // Spectat mode
        {
            sleep(BUSY_WAITING);

            read(sock, message,sizeof(message)); // server측에서 보낸 데이터 수신

                if(strcmp(message, "pass") == 0) // pass 이라면 
                {
                    isInput = true;
                    inputMode();
                    break;
                }

                if(strcmp(message, "quit") == 0) //quit 이라면 
                {
                    printf("%s님이 나가셨습니다",servUserName);
                    exit(1);
                }

        printf("\n%s> %s\n",servUserName, message); //server 측에서 보낸 메세지 출력
        } // while(isInput == SPECTATMODE)
    } // while(true)
} // int main(생략)




