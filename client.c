/*/////////////////
client 입니다.
*//////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "need.h"

int clnt_connect(int PAF, const char * const servIP, const unsigned short port);

int main(int argc, char * argv[])
{
    
    system("clear"); //console claer
 
    char Message[BUF_SIZE]; //전송 및 수신 데이터
    char servUserName[BUF_SIZE]; // 클라이언트측 이름

    int sock; // 소켓 
    int flag; // 데이터 송수신 컨트롤 변수
 
    

    if(argc != 4) // 올바른 사용법인지 확인
    {
        printf("Usage : %s <IP> <PORT> <NAME>\n", argv[0]);
        exit(1);
    }

    /*
        argv[0] : ./exe
        argv[1] : IP
        argv[2] : PORT
        argv[3] : NAME
    */


   

    sock = clnt_connect(AF_INET, argv[1], atoi(argv[2]));
        if(sock == -1) error_handling("connect() error");
   

        write(sock, argv[3], sizeof(argv[3])); // Server에게 Client가 사용하는 이름 송신

        read(sock, servUserName, sizeof(servUserName)); // Client에서 사용하는 이름 Server에게 수신
        printf("연결!");
}
/*
    int clnt_connect(int PAF, const char * const servIP, unsigned short port)
    int PAF : 프로토콜 체계, 주소 체계
    servIP : IP값 (IP는 대상의 값이랑 주소값은 바뀌면 안되므로 Const로 선언)
    unsigned short prot : port 데이터 

*/
int clnt_connect(int PAF, const char * const servIP, const unsigned short port)
{

    struct sockaddr_in serv_addr; // 서버 주소 정보 구조체
    int sock;


    sock = socket(PAF, SOCK_STREAM, 0); // 소켓생성
        if(sock == -1)  return SOCKET_ERROR;
    

    memset(&serv_addr, 0, sizeof(serv_addr)); // sin_zero[8] 초기화 

    serv_addr.sin_family = PAF; //IPv4
    inet_pton(PAF, servIP, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port); // PORT

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) //연결
        return -2;
    else
        return sock;
}





