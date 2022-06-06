#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1020 // Buffer size

void error_handling(char * message) //에러 
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


int main(int argc, char * argv[])
{

    int speak = 1; //채팅 방식 컨트롤 변수

    int serv_sock, clnt_sock; // Server socket, Client socket

    char writeMessage[BUF_SIZE]; // 전송데이터
    char readMessage[BUF_SIZE]; // 수신데이터

    char servUserName[BUF_SIZE]; // 서버측 이름
    char clntUserName[BUF_SIZE]; // 클라이언트측 이름


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
    
    

    while(1) // client 송수신
    {

        printf("%s> ",servUserName); 
        fgets(readMessage, BUF_SIZE, stdin);
        write(clnt_sock,readMessage,sizeof(readMessage));

        sleep(0.5);

        read(clnt_sock, readMessage, sizeof(readMessage));
        printf("\n%s : %s\n",clntUserName,readMessage);

        sleep(0.5);
    }


    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}