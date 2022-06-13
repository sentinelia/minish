#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int builtin_setenv (int argc, char ** argv){

    if(argc != 3){
        printf('error en el formato del comando, debe ingresar el nombre de la variable y el valor que le desea asignar');
        return 0;
    }

    char variable = argv[1];
    char valor = argv[2];

    char *string = malloc(strlen(variable)+strlen(valor)+2);

    strcpy(string,variable);
    strcat(string,'=');
    strcat(string,valor);

    if( putenv(string) == 0) {
        return 0;
    }else{
        printf('error');
    }


    
}