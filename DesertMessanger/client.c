#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "show.h"

#define BUF_SIZE 1020 //Buffer size

void error_handling(char * message); //error

int main(int argc, char * argv[])
{
    
    system("clear"); //console claer
 
    char writeMessage[BUF_SIZE]; //전송 데이터
    char readMessage[BUF_SIZE]; //수신 데이터

    char servUserName[BUF_SIZE]; // 서버측 이름
    char clntUserName[BUF_SIZE]; // 클라이언트측 이름

    struct sockaddr_in serv_addr; // 서버 주소 정보 구조체
    int sock; // 소켓 
    int flag = 0; // 데이터 송수신 컨트롤 변수
 
    


    if(argc != 3) // 올바른 사용법인지 확인
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    if((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) // 소켓생성
        error_handling("socket() error");
    

    memset(&serv_addr, 0, sizeof(serv_addr)); // sin_zero[8] 초기화 
    serv_addr.sin_family = AF_INET; //IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //IP
    serv_addr.sin_port = htons(atoi(argv[2])); // PORT

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) //연결
        error_handling("connect() error");


        read(sock, servUserName,sizeof(servUserName)); // servUserName 데이터 수신

        sleep(0.5); //Busy Waiting

        printf("Enter the Name\n> ");
        fgets(clntUserName, BUF_SIZE, stdin);
        clntUserName[strlen(clntUserName) -1] = '\0'; //개행 지워주기

        write(sock, clntUserName, sizeof(clntUserName)); // server에  clntUserName 데이터 송신
        sleep(0.5); // Busy Waiting

        //printf("servName : %s  clntName : %s\n",servUserName, clntUserName); // 데이터 송수신 잘 되어는지 확인
        

    puts("관전모드 입니다.");
    flag = 0;
    
    while(1)
    {
        if(flag == 1)
            while(1)
            {
                printf("\n%s> ",clntUserName);
                fgets(writeMessage, BUF_SIZE, stdin); 
                writeMessage[strlen(writeMessage)-1] = '\0';

                if(strcmp(writeMessage, "help") == 0)
                 _help();

                if(strcmp(writeMessage, "quit") == 0)
                {
                    printf("종료합니다.\n");
                    write(sock,"quit",5);
                    close(sock);
                    exit(1);
                }

                if(strcmp(writeMessage, "pass") == 0)
                {
                    write(sock, "pass", 5); 
                    flag = 0;
                    puts("관전모드 입니다.");
                    break;
                }
           
                write(sock, writeMessage, sizeof(clntUserName));
               
            }

        if(flag == 0)
            while(1)
            {
                
                read(sock, readMessage,sizeof(readMessage));
                if(strcmp(readMessage, "quit") == 0)
                {
                    printf("%s님이 나가셨습니다.\n",servUserName);
                    close(sock);
                    exit(1);
                }
                if(strcmp(readMessage, "pass") == 0)
                {
                    flag = 1;
                    puts("입력모드 입니다");
                    break;
                }
            
                printf("\n%s> %s\n",servUserName, readMessage);
            }
        
    } 

    close(sock);
    return 0;
}

void error_handling(char * message) //error
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}