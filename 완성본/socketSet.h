/*/////////////////
socketSet.h 입니다.
*//////////////////

// DEFINE SET
#define SOCKET_ERROR -1 //소켓 에러
#define BIND_ERROR -2 // 바인드 에러
#define LISTEN_ERROR -3 // 리슨 에러

#define CONNECT_ERROR -4 // 컨넥트 에러

#define INPUTMODE 1
#define SPECTATMODE 0

/////////////////////////////////////////


int serv_listen(int PAF, const char * const servIP, const unsigned short port, const int listen_backLog)
{

    int serv_sock;
    struct sockaddr_in serv_addr; //서버 , 클라이언트 주소 정보 구조체

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
        if(serv_sock == -1) return SOCKET_ERROR;


    memset(&serv_addr, 0, sizeof(serv_addr)); // sin_zero[8] 초기화 
    serv_addr.sin_family = PAF; //IPv4
    inet_pton(PAF, servIP, &serv_addr.sin_addr); //IP
    serv_addr.sin_port = htons(port); // PORT

    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // serv_sock에 주소정보 할당
        return BIND_ERROR;

    if(listen(serv_sock, listen_backLog) == -1) // listen 
        return LISTEN_ERROR;

    return serv_sock;

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

    struct sockaddr_in serv_addr; // 서버 주소 정보 구조체
    int sock;


    sock = socket(PAF, SOCK_STREAM, 0); // 소켓생성
        if(sock == -1)  return SOCKET_ERROR; // 만약 생성 오류시 SOCKET_ERROR 반환
    

    memset(&serv_addr, 0, sizeof(serv_addr)); // sin_zero[8] 초기화 
    serv_addr.sin_family = PAF; //IPv4
    inet_pton(PAF, servIP, &serv_addr.sin_addr); // IP
    serv_addr.sin_port = htons(port); // PORT

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) //연결
        return CONNECT_ERROR; //만약 connect 오류시 CONNECT_ERROR 반환

    return sock; // 소켓 반환
}

/*
    int clnt_connect(int PAF, const char * const servIP, unsigned short port)

    int PAF : 프로토콜 체계, 주소 체계
    servIP : IP값 (IP는 대상의 값이랑 주소값은 바뀌면 안되므로 Const로 선언)
    unsigned short prot : port 데이터 

*/