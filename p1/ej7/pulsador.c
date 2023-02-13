#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char opcion[10], respuesta;

    printf("------------------\n");
    printf("|    ASCENSOR    |\n");
    printf("------------------\n");

    do{
        printf("\n1. Subir de piso\n");
        printf("2. Bajar de piso\n");
        printf("3. Salir\n");
        printf("Escoja una opcion (123): ");
        fgets(opcion,10,stdin);
        respuesta = opcion[0];

        switch(respuesta){
            case '1':
                printf("\nHa elegido SUBIR\n");
                kill(atoi(argv[1]), 10);
                break;
            case '2':
                printf("\nHa elegido BAJAR\n");
                kill(atoi(argv[1]), 12);
                break;
            case '3':
                printf("\nHa elegido SALIR\n");
                kill(atoi(argv[1]), 3);
                break;
        }

    }while(respuesta != '3');

    return 0;
}

