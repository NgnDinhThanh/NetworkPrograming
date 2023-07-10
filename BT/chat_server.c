#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <cctype>
#include <pthread.h>
#include <signal.h>

void *client_thread(void *);
void *JOIN(void *);
void signal_handler(int signo)
{
    wait(NULL);
}

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1) {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    signal(SIGPIPE, signal_handler);

    while(1) 
    {
        int client = accept(listener, NULL, NULL);
        if (client == -1)
        {
            perror("accept() failed");
            continue;
        }
        printf("New client connected: %d\n", client);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, client_thread, &client);
        pthread_detach(thread_id);
    }
    close(listener);
    return 0;
}

void *JOIN(void *param) 
{
    int client = *(int *) param;
    char buf[2048];
    int num_clients;
    string clients[2048];

    int ret = recv(client, buf, sizeof(buf) - 1, 0);
    if (ret <= 0)
        return NULL;
    buf[ret] = 0;
    char *p;
    strcpy(p, strchr(buf, " ")+1);
    nu
    
}
