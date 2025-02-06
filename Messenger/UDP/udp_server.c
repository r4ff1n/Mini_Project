//소켓 생성, 바인딩, 리슨, 클라이언트 연결, 데이터 송수신
// socket(), bind(), listen(), accept(), send(), recv(), close()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(){
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
}