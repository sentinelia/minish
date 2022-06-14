#include <string.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int builtin_cd (int argc, char ** argv){
    if (argc > 2){
        err(1, "Error, demasiados argumentos.");
    } else {
        if (argc == 2){
            if (chdir("/*argv[1]") == 0){ //cambia al directorio que me pasaron
                return 0; 
            }
        }
        if (argc == 1){  
            if (chdir("/home") == 0){  //cambia al directorio de la variable home
                return 0; 
            }
        }
        if (*argv[1] == '-'){
            if (chdir("..") == 0){  //cambia al directorio anterior
                return 0; 
            } 
        }
    }
    
    return 0;
    
    
}


