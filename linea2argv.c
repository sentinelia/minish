#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minish.h"


int linea2argv (char *linea, int argc, char **argv){
    int k=0;
    int csum = 0; //VARIABLE BOOLEANA INDICA SI DEBE SUMAR AL CONTADOR DE PALABRAS
    int wrdq = 0; //CANTIDAD DE PALABRAS

    //ESTE LOOP SEPARA LAS PALABRAS POR ESPACIO O TAB Y LAS PONE EN UN ARRAY
    //TOMA EN CUENTA QUE HAYAN 2 ESPACIOS JUNTOS
    for(int i=0; linea[i]!='\0';i++){
        if((linea[i]==' '||linea[i]=='\n'||linea[i]=='\t') && csum==1){ //SI PUEDO CONTAR Y ENCUENTRO ESPACIO O SALTO DE LINEA, SUMO
            argv[wrdq][k]='\0';
            wrdq++;
            k=0;
            csum = 0;
            
        } else if(linea[i]!=' ' && linea[i]!='\n' && linea[i]!='\t'){ //SI VUELVO A ENCONTRAR UN CARACTER PUEDO VOLVER A SUMAR
            csum=1;
            argv[wrdq][k]=linea[i];
            k++;
        }
    }
    //EL ULTIMO ELEMENTO DEBE SER NULO
    argv[wrdq]=NULL;
    return wrdq;
    
}

