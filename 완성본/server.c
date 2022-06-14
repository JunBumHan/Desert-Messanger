/*/////////////////
server 입니다.
*//////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "show.h"
#include "socketSet.h"

int main(int argc, char * argv[])
{
    system("clear"); // 콘솔 clear
    
    if(argc != 4) // 올바른 사용법인지 확인
    {
        printf("Usage : %s <IP> <PORT> <NAME>\n", argv[0]);
        exit(1);
    }
    /*
        argv[0] : ./exe
        argv[1] : IP
        argv[2] : PORT
        argv[3] : servName
    */


    int serv_sock, clnt_sock; // Server socket, Client socket

    char message[BUF_SIZE]; // Message

    char clntUserName[NAME_SIZE]; // client user name   

    struct sockaddr_in clnt_addr;  //클라이언트 주소 정보 구조체
    socklen_t clnt_addr_size; // accpet 함수에서 사용할 clnt_addr 구조체 크기
    


    serv_sock = serv_listen(PF_INET, argv[1], atoi(argv[2]), 1); 
    
    switch(serv_sock)
    {
        case SOCKET_ERROR: error_handling("socket() error");
        case BIND_ERROR: error_handling("bind() error");
        case LISTEN_ERROR: error_handling("listen() error");
    }



    clnt_addr_size = sizeof(clnt_addr); // accept 세번 쨰 인자값을 위해
    if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1) // accpet
        error_handling("accpet() error");
    
        read(clnt_sock, clntUserName, sizeof(clntUserName)); // Server에서 사용하는 이름 Client에게 수신 
        sleep(0.5);
        write(clnt_sock, argv[3], sizeof(argv[3])); // Client 에게 Server가 사용하는 이름 송신



    sleep(0.5);
    bool isInput = true;
    inputMode();

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
                    write(clnt_sock, "pass", 5);
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
                    write(clnt_sock, "quit", 5); 
                    close(clnt_sock);
                    close(serv_sock);
                    exit(1);
                }

            write(clnt_sock, message,sizeof(message)); // clnt에게 입력한 데이터 전송
        }

        while(isInput == SPECTATMODE)
        {

            sleep(0.5);
            read(clnt_sock, message, sizeof(message));

                if(strcmp(message, "pass") == 0)
                {
                    isInput = true;
                    inputMode();
                    break;
                }

                if(strcmp(message, "quit") == 0)
                {
                    printf("%s님이 나가셨습니다",clntUserName);
                    exit(1);
                }

            printf("\n%s> %s\n",clntUserName, message);

        }
    }

}

