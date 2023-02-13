#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define LONGITUD 31
int finalizar = 0;
int sinales[LONGITUD];

//Accion que se lleva al cabo al recibir una sinal
void sighandler(int sinal){
    sinales[sinal-1] = 1;
    if(sinal == 15){
        finalizar = 1;
        printf("Lista de sinales recibidas: \n");
        for(int i = 0; i < LONGITUD; i++) printf("%d", sinales[i]);
        printf("\n");
    }
}

int main(){
    struct sigaction sigact;
    int i;

    printf("PID: %d\n", getpid());

    //Inicializacion del vector de sinales recibidas
    for(i = 0; i < LONGITUD; i++) sinales[i] = 0;

    sigact.sa_handler = sighandler;
    for(i = 1; i <= LONGITUD; i++){
        if(sigaction(i, &sigact, NULL) < 0) printf("Error: Sinal %d\n", i);
    }

    while(!finalizar) pause();

    return 0;
}
