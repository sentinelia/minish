#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minish.h"


int linea2argv (char *linea, int argc, char **argv){
    int k=0;
    int csum = 0; //VARIABLE BOOLEANA INDICA SI DEBE SUMAR AL CONTADOR DE PALABRAS
    int wrdlength = 0;

    for(int i=0; linea[i]!='\0';i++){
        if((linea[i]==' '||linea[i]=='\n') && csum==1){ //SI PUEDO CONTAR Y ENCUENTRO ESPACIO O SALTO DE LINEA, SUMO
            argv[wrdlength][k+1]='\0';
            wrdlength++;
            k=0;
            csum = 0;
            
        } else if(linea[i]!=' ' && linea[i]!='\n'){ //SI VUELVO A ENCONTRAR UN CARACTER PUEDO VOLVER A SUMAR
            csum=1;
            argv[wrdlength][k]=linea[i];
            k++;
            
        }
    }
    return wrdlength;
    
}

