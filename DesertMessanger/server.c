#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "show.h"


#define BUF_SIZE 1020 // Buffer size

void error_handling(char * message);

int main(int argc, char * argv[])
{
    system("clear");
    

    int serv_sock, clnt_sock; // Server socket, Client socket

    char writeMessage[BUF_SIZE]; // 전송데이터
    char readMessage[BUF_SIZE]; // 수신데이터

    char servUserName[BUF_SIZE]; // 서버측 이름
    char clntUserName[BUF_SIZE]; // 클라이언트측 이름

    int flag = 1; //채팅 방식 컨트롤 변수

    struct sockaddr_in serv_addr, clnt_addr;  //서버 , 클라이언트 주소 정보 구조체

    socklen_t clnt_addr_size; // accpet 함수에서 사용할 clnt_addr 구조체 크기
    



    if(argc != 2) // 올바른 사용법인지 확인
    {
        printf("Usage : %s <Port>\n", argv[0]);
        exit(1);
    }
    //argv[1] : port


    if((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) // 서버 소켓 생성
        error_handling("socket() error");


    memset(&serv_addr, 0, sizeof(serv_addr)); // sin_zero[8] 초기화
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP
    serv_addr.sin_port = htons(atoi(argv[1])); // Port
    
    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // serv_sock에 주소정보 할당
        error_handling("bind() error");

    if(listen(serv_sock, 1) == -1) // listen 
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr); // accept 세번 쨰 인자값을 위해
    if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1) // accpet
        error_handling("accpet() error");
    
        printf("Enter the Name\n> ");
        fgets(servUserName, BUF_SIZE, stdin); //입력
        servUserName[strlen(servUserName) - 1] = '\0'; // 개행 지워주기

        write(clnt_sock, servUserName, strlen(servUserName)); // Client에게 servUserName 데이터 송신

        sleep(0.5); // Busy Waiting

        read(clnt_sock, clntUserName,sizeof(clntUserName)); // ClntUserName 데이터 수신
        //printf("servName : %s , clntName : %s\n",servUserName, clntUserName); // 데이터 송수신 잘 되어는지 확인
    

    puts("입력모드 입니다.");
    flag = 1;


    while(1)
    {
        if(flag == 1)
            while(1)
            {
                
                printf("\n%s> ",servUserName);
                fgets(writeMessage, BUF_SIZE, stdin); writeMessage[strlen(writeMessage)-1] = '\0';

                if(strcmp(writeMessage, "help") == 0)
                 _help();

                if(strcmp(writeMessage, "quit") == 0)
                {
                    printf("종료합니다.\n");
                    write(clnt_sock, "quit", 5);
                    close(clnt_sock);

                    close(serv_sock);
                    
                    exit(1);
                }


                if(strcmp(writeMessage, "pass") == 0)
                {
                    write(clnt_sock, "pass", 5);
                    flag = 0;
                    puts("관전모드 입니다.");
                    break;
                }
           
            write(clnt_sock, writeMessage,sizeof(writeMessage));
            //printf("%s\n",writeMessage);
            
        }
        sleep(1);
        if(flag == 0)
            while(1)
            {
                

                read(clnt_sock, readMessage,sizeof(readMessage));

                if(strcmp(readMessage, "quit") == 0)
                {
                    printf("%s님이 나가셨습니다.\n",clntUserName);
                    close(clnt_sock);
                    close(serv_sock);
                    exit(1);
                }
                
                if(strcmp(readMessage, "pass") == 0)
                {
                    flag = 1;
                    puts("입력모드 입니다");
                    break;
                }

                printf("\n%s> %s\n",clntUserName, readMessage);
                
            }

        

    } 

}

void error_handling(char * message) //에러 
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}