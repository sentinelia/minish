#include <stdio.h>
#include <dirent.h>
#include "minish.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <err.h>



int builtin_history (int argc, char ** argv){

    int n;

    if (argc > 2){
        err(1, "Error en la cantidad de argumentos.");
    } else {
        if (argc == 1){
            n = 10; 
        }
        else if (argc == 2){
            n = argv[1];
        }
    }

    struct node *temp;
    temp = history -> ultimo;

    for(int i = 0; i < n; i++ ){
        printf("%s\n",temp->cmd);
        temp=temp->anterior;
    }
    
    return EXIT_SUCCESS;

}
