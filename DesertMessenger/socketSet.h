/*/////////////////
socketSet.h 입니다.
*//////////////////

// DEFINE SET
#define SOCKET_ERROR -1  // SOCKET ERROR
#define BIND_ERROR -2    // BIND ERROR
#define LISTEN_ERROR -3  // LISTEN ERROR

#define CONNECT_ERROR -4 // CONNECT ERROR

#define INPUTMODE 1      // INPUTMODE
#define SPECTATMODE 0    // SPECTATMODE

#define BUSY_WAITING 0.5 // BUSY_WAITING

///////////////////////

int serv_listen(int PAF, const char * const servIP, const unsigned short port, const int listen_backLog)
{

    int serv_sock;                // Server Socket
    struct sockaddr_in serv_addr; // 서버 , 클라이언트 주소 정보 구조체

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
        if(serv_sock == -1) return SOCKET_ERROR; // 소켓 생성 오류시 SOCKET_ERORR 반환 


    memset(&serv_addr, 0, sizeof(serv_addr));    // sin_zero[8] 초기화 
    serv_addr.sin_family = PAF;                  // IPv4
    inet_pton(PAF, servIP, &serv_addr.sin_addr); // IP
    serv_addr.sin_port = htons(port);            // PORT

    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // serv_sock 에 주소정보 할당
        return BIND_ERROR; // 바인드 오류시 BIND_ERROR 반환 

    if(listen(serv_sock, listen_backLog) == -1) // Listen() 
        return LISTEN_ERROR; // 리슨 오류시 LISTEN_ERROR 반환 

    return serv_sock; // serv_sock 반환 
}

/*
    int serv_listen(int PAF, const char * const servIP, const unsigned short port, const int listen_backLog)
    : socket 생성부터 listen까지의 과정을 해주는 함수


    int PAF : 프로토콜 체계, 주소 체계
    servIP : IP값 (IP는 대상의 값이랑 주소값은 바뀌면 안되므로 Const로 선언)
    unsigned short prot : port 데이터 
    listen_backLog : listen 대기 큐 

*/




int clnt_connect(int PAF, const char * const servIP, const unsigned short port)
{

    int sock;                     // Socket
    struct sockaddr_in serv_addr; // 서버 주소 정보 구조체

    sock = socket(PAF, SOCK_STREAM, 0);      // 소켓생성
        if(sock == -1)  return SOCKET_ERROR; // 소켓 생성 오류시 SOCKET_ERROR 반환
    

    memset(&serv_addr, 0, sizeof(serv_addr));    // sin_zero[8] 초기화 
    serv_addr.sin_family = PAF;                  // IPv4
    inet_pton(PAF, servIP, &serv_addr.sin_addr); // IP
    serv_addr.sin_port = htons(port);            // PORT

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // connect()  
        return CONNECT_ERROR; // connect 오류시 CONNECT_ERROR 반환

    return sock; // 소켓 반환
}

/*
    int clnt_connect(int PAF, const char * const servIP, unsigned short port)

    int PAF : 프로토콜 체계, 주소 체계
    servIP : IP값 (IP는 대상의 값이랑 주소값은 바뀌면 안되므로 Const로 선언)
    unsigned short prot : port 데이터 

*/