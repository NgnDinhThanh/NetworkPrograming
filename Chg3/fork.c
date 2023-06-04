#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before FORK\n");
    int cid = fork();
    printf("After FORK, PID = %d \n", cid);
    return 0;
 }