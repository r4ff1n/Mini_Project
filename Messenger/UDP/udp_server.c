// 소켓 생성, 바인딩, 리슨, 클라이언트 연결, 데이터 송수신
//  socket(), bind(), listen(), accept(), send(), recv(), close()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000
#define BUF_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    printf("buffer pointer : %p\n",buffer);
    printf("buffer data : %d\n",&buffer);
    printf("buffer data : %d\n",*buffer);
    printf()
    socklen_t addr_len = sizeof(client_addr);
    // 1. UDP 소켓 생성
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        perror("소켓 생성 실패");
        exit(1);
    }
    // 2. 서버 주소 구조체 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. 소켓을 포트에 바인딩
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("바인딩 실패");
        close(sock);
        exit(1);
    }
    printf("UDP 서버 포트: %d\n", PORT);

    // 4. 데잇터 수신 및 응답
    while(1){
        memset(buffer, 0, BUF_SIZE);
        int recv_len = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if(recv_len == -1){
            perror("데이터 수신 실패");
            break;
        }
        printf("Client:(%s:%d)\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        char response[BUF_SIZE];
        sprintf(response, "UDP 서버 응답: %s",buffer);
        if (sendto(sock, response, strlen(response), 0, (struct sockaddr*)&client_addr, addr_len) == -1) {
            perror("응답 전송 실패");
            break;
        }        
    }
}
