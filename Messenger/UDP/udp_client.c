// 소켓 생성, 연결, 데이터 송수신, 종료
// socket(), connect(), send(), recv(), close() 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sock;

    // 1. 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("소켓 생성 실패");
        exit(1);
    }
    printf("소켓 생성 성공!\n");

    // 2. 소켓 닫기
    close(sock);
    printf("소켓 닫기 완료\n");

    return 0;
}