#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>


int builtin_setenv (int argc, char ** argv){

    if(argc != 3){
        err(1,"error en el formato del comando, debe ingresar el nombre de la variable y el valor que le desea asignar");
    }else{
        printf("%s\n", setenv(*argv[1], *argv[2], 1));
        return(0);
        }
    
}