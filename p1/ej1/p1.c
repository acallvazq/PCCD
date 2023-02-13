#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
    printf("PID: %d\n", getpid());

    pause();
    return 0;
}
