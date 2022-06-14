#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int builtin_setenv (int argc, char ** argv){

    if(argc != 3){
        printf("error en el formato del comando, debe ingresar el nombre de la variable y el valor que le desea asignar");
        return 0;
    }

    setenv(argv[1],argv[2],1);

    return 0;
    
}