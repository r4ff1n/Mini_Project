#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // 서버 IP (로컬 서버)
#define SERVER_PORT 9000      // 서버 포트
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // 1. UDP 소켓 생성
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("소켓 생성 실패");
        exit(1);
    }

    // 2. 서버 주소 구조체 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("서버 IP 주소 변환 실패");
        exit(1);
    }

    // 3. 사용자로부터 메시지 입력 받기
    printf("서버로 보낼 메시지를 입력하세요: ");
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // 입력된 문자열에서 개행 문자 제거

    // 4. 서버로 메시지 전송
    if (sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("서버로 메시지 전송 실패");
        close(sock);
        exit(1);
    }

    // 5. 서버로부터 응답 수신
    socklen_t addr_len = sizeof(server_addr);
    int recv_len = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (recv_len == -1) {
        perror("서버 응답 수신 실패");
        close(sock);
        exit(1);
    }

    buffer[recv_len] = '\0';  // 응답 메시지 종료 문자 추가
    printf("서버 응답: %s\n", buffer);

    // 6. 소켓 종료
    close(sock);
    return 0;
}
