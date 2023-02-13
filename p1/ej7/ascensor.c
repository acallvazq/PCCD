#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRIMERO 1
#define T_PISO 3
int ultimoPiso;
int posicion;
int numSubir = 0;
int numBajar = 0;
bool trabaja = false;
int finalizar = 0;
int* sensores;

//Accion que se lleva al cabo al recibir una sinal
void sighandler(int sinal){
    if(sinal == 14){
        trabaja = false;
        printf("Ha llegado al piso %d\n", posicion);
    }else if(sinal == 10) {
        if(posicion >= ultimoPiso) printf("Este es el ultimo piso\n");
        else if(trabaja) return;
        else {
            printf("Subiendo de piso...\n");
            posicion++;
            numSubir++;
            trabaja = true;
            if(sensores[posicion-1] != 0)kill(sensores[posicion-1],10);
        }

    }else if(sinal == 12){
        if(posicion <= PRIMERO) printf("Este es el primer piso\n");
        else if(trabaja) return;
        else{
            printf("Bajando de piso...\n");
            posicion--;
            numBajar++;
            trabaja = true;
            if(sensores[posicion-1] != 0)kill(sensores[posicion-1],10);
        }
    }else if(sinal == 3){
        finalizar = 1;
        printf("Se ha subido %d veces y bajado %d veces\n", numSubir, numBajar);
    }
}

int main(int argc, char* argv[]){
    struct sigaction sigact;
    char linea[50];

    printf("PID: %d\n", getpid());

    posicion = 1;
    ultimoPiso = atoi(argv[1]);
    sensores = (int*)malloc(ultimoPiso * sizeof(int));

    for(int i = 0; i < ultimoPiso; i++){
        printf("PID del sensor situado en el piso %d: ", i+1);
        fgets(linea,50,stdin);
        sensores[i] = atoi(linea);
    }

    sigact.sa_handler = sighandler;
    if(sigaction(14, &sigact, NULL) < 0) printf("Error: Sinal 14\n");
    if(sigaction(10, &sigact, NULL) < 0) printf("Error: Sinal 10\n");
    if(sigaction(12, &sigact, NULL) < 0) printf("Error: Sinal 12\n");
    if(sigaction(3, &sigact, NULL) < 0) printf("Error: Sinal 3\n");

    while(!finalizar) pause();

    free(sensores);

    return 0;
}
