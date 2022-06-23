#include <stdio.h>
#include <dirent.h>
#include "minish.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <err.h>

#define MAXLINE 1024


int builtin_history (int argc, char ** argv){
    FILE *history;
    char line[MAXLINE]; 
    int len,i,n; 
    char *lp;  
    int file_len = 0;
    char *file_lines[file_len]; 

    if (argc > 2){
        err(1, "Error en la cantidad de argumentos.");
    } else {
        if (argc == 1){
            n = 10; 
        }
        else if (argc == 2){
            n = argv[1];
        }
        
        for (i = 0; fgetln(history, MAXLINE) > 0; i++){
            file_len++; //cuenta la cantidad de lineas totales en el txt
        }
        if (file_len <= n){ //si hay menos lineas de las deseadas
            for (i = 0; i < file_len; i++){
                lp = fgets(line, MAXLINE, history);
                printf("%s\n",lp); //imprime todas las lineas del txt
            }
            return 0; //EXIT_SUCCESS
        } else {
            for (i = 0; i < file_len && (len = fgetln(history, MAXLINE)) > 0; i++){
                file_lines[i] = malloc(len+1);
                strcpy(file_lines[i], line);
            }

            int inicio = file_len - n; //calcula la posicion inicial a partir de la cual se comienza a imprimir
            for (i = inicio; n-- > 0; i = (i+1) % n){
                printf("%s\n", file_lines[i]);
            }
            return 0; 
        }
    }
    return 1; 



    
}