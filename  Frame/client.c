#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1020

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char * argv[])
{

    char message[BUF_SIZE];
    char servMessage[BUF_SIZE];

    int sock; // 클라이언트 소켓 
    
    struct sockaddr_in serv_addr; // 서버 주소 정보
    
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    read(sock, message, sizeof(message)-1);
    printf("server : %s",message);

    
    printf("입력 : "); fgets(message, BUF_SIZE, stdin); strcpy(servMessage, message);
    write(sock, message, sizeof(message));

    close(sock);

    return 0;
    


}