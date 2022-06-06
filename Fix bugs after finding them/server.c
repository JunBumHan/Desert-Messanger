#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1020 // Buffer size
int n;

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}



int main(int argc, char * argv[])
{
    int speak = 1;

    int serv_sock, clnt_sock; // Server socket, Client socket

    char writeMessage[BUF_SIZE];
    char readMessage[BUF_SIZE];
    int str_len; // string length

    struct sockaddr_in serv_addr, clnt_addr; 
    socklen_t clnt_addr_size; // accpet 함수에서 사용할 clnt_addr 구조체 크기


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

    clnt_addr_size = sizeof(clnt_addr);
    if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1) // accpet
        error_handling("accpet() error");
    
    printf("입력:"); scanf("%s",readMessage);
    write(clnt_sock,readMessage,sizeof(readMessage));

    sleep(2);

    read(clnt_sock, readMessage, sizeof(readMessage));
    printf("\n출력 : %s\n",readMessage);
     
    sleep(2);
    
    printf("입력:"); scanf("%s",readMessage);
    write(clnt_sock,readMessage,sizeof(readMessage));

    sleep(2);

    read(clnt_sock, readMessage, sizeof(readMessage));
    printf("\n출력 : %s\n",readMessage);
    
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting
//데이터 송수신 할 때 Busy Waiting

    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}