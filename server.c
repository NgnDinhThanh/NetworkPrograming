#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    // Tao socket
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1) 
    {
        perror("socket() failed");
        return 1;
    }

    // Khai bao cau truc dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    //Gan dia chi voi socket
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listener() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    int clientAddrlen = sizeof(clientAddr);

    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrlen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    char *msg = "Hello client\n";
    send(client, msg, strlen(msg), 0);

    char buf[256];

    while(1) 
    {
        int ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            printf("Ket noi bi dong.\n");
            break;
        }
        if (ret < sizeof(buf))
            buf[ret] = 0;
        
        printf("%d byte received\n", ret);
        printf("%s\n", buf);
    }

    close(client);
    close(listener);
}