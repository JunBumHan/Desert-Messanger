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
    system("clear"); // console clear
    
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

    // Variable declaration
    int serv_sock, clnt_sock; // Server socket, Client socket

    char message[BUF_SIZE];       // Message
    char clntUserName[NAME_SIZE]; // Client User Name  

    struct sockaddr_in clnt_addr;  //클라이언트 주소 정보 구조체
    // // // // // //

    socklen_t clnt_addr_size; // accpet 함수에서 사용할 clnt_addr 구조체 크기
    

    serv_sock = serv_listen(PF_INET, argv[1], atoi(argv[2]), 1); // listen까지 수행한 뒤 파일드스크립트 저장
    
    switch(serv_sock) // Error 검사
    {
        case SOCKET_ERROR: error_handling("socket() error"); // SOCKET_ERROR
        case BIND_ERROR: error_handling("bind() error");     // BIND_ERROR
        case LISTEN_ERROR: error_handling("listen() error"); // LISTEN_ERROR
    }

    clnt_addr_size = sizeof(clnt_addr); // accept() 3rd argument value
    if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1) // accpet()
        error_handling("accpet() error");
    
        read(clnt_sock, clntUserName, sizeof(clntUserName)); // Server에서 사용하는 이름 Client에게 수신 
        sleep(BUSY_WAITING);
        write(clnt_sock, argv[3], sizeof(argv[3]));          // Client에게 Server가 사용하는 이름 송신



    sleep(BUSY_WAITING);

    bool isInput = true;
    inputMode(); // Input mode

    while(true)  // Infinite loop
    {
        while(isInput == INPUTMODE) // Input mode
        {
            sleep(BUSY_WAITING);
            
            printf("\n%s> ",argv[3]); // servName 출력
            fgets(message, BUF_SIZE, stdin); // 입력 
            message[strlen(message)-1] = 'NULL'; // 개행(enter) 지워주기


                if(strcmp(message, "pass") == 0) // pass 이라면
                {
                    isInput = false;
                    spectatMode();
                    write(clnt_sock, "pass", 5);
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
                    write(clnt_sock, "quit", 5); 
                    close(clnt_sock);
                    close(serv_sock);
                    exit(1);
                }

        write(clnt_sock, message,sizeof(message)); // client 에게 입력한 데이터 전송

        } // while(isInput == INPUTMODE)

        while(isInput == SPECTATMODE) // Spetat mode
        {
            sleep(BUSY_WAITING);

            read(clnt_sock, message, sizeof(message)); // client 측에서 보낸 데이터 수신

                if(strcmp(message, "pass") == 0) // pass 이라면
                {
                    isInput = true;
                    inputMode();
                    break;
                }

                if(strcmp(message, "quit") == 0) // quit 이라면 
                {
                    printf("%s님이 나가셨습니다",clntUserName);
                    exit(1);
                }

        printf("\n%s> %s\n",clntUserName, message); // client 측에서 보낸 메세지 출력
        } // while(isInput == SPECTATMODE)
    } // while(true)
} // int main(생략)

