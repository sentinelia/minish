#include <stdlib.h>

int builtin_exit (int argc, char ** argv){
    exit(0);
    return argv[1]!=0 ? 1: 0; //RETORNO 0 SI EL PRIMER ARGUMENTO ES DISTINTO DE 0, 1 SI ES CUALQUIER OTRA COSA
}