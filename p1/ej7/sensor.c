#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define PRIMERO 1
#define T_PISO 3
int finalizar = 0;
int piso;
int ascensor;

//Accion que se lleva al cabo al recibir una sinal
void sighandler(int sinal){
    if(sinal == 10) {
        sleep(T_PISO);
        printf("El sensor del piso %d se ha activado\n", piso);
        kill(ascensor, 14);
    }else if(sinal == 3){
        finalizar = 1;
        printf("Apagando sensor del piso %d...\n", piso);
    }
}

int main(int argc, char* argv[]){
    struct sigaction sigact;

    printf("PID: %d\n", getpid());

    piso = atoi(argv[1]);		// piso donde esta situado el sensor
    ascensor = atoi(argv[2]);	        // pid de ascensor.c
    sigact.sa_handler = sighandler;

    if(sigaction(10, &sigact, NULL) < 0) printf("Error: Sinal 10\n");
    if(sigaction(3, &sigact, NULL) < 0) printf("Error: Sinal 3\n");

    while(!finalizar) pause();

    return 0;
}
