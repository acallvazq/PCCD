#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    //argv[1] es el pid y argv[2] la sinal
    kill(atoi(argv[1]), atoi(argv[2]));

    return 0;
}
