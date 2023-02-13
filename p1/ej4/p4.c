#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int finalizar = 0;
int cont_USR1;
int cont_USR2;

//Accion que se lleva al cabo al recibir una sinal
void sighandler(int sinal){
    if(sinal == 10) ++cont_USR1;
    else if(sinal == 12) ++cont_USR2;
    else if(sinal == 15){
        finalizar = 1;
        printf("Se ha recibido %d SIGUSR1 y %d SIGUSR2\n", cont_USR1, cont_USR2);
    }
}

int main(){
    struct sigaction sigact;

    printf("PID: %d\n", getpid());

    cont_USR1 = cont_USR2 = 0;
    sigact.sa_handler = sighandler;
    if(sigaction(10, &sigact, NULL) < 0) printf("Error: Sinal 10\n");
    if(sigaction(12,&sigact, NULL) < 0) printf("Error: Sinal 12\n");
    if(sigaction(15, &sigact, NULL) < 0) printf("Error: Sinal 15\n");

    while(!finalizar) pause();

    return 0;
}
