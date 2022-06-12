#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int wordcount(char linea[]){
    int csum = 0; //VARIABLE BOOLEANA INDICA SI DEBE SUMAR AL CONTADOR DE PALABRAS
    int wrdlength = 0;
    for(int i=0; linea[i]!='\0';i++){
        if((linea[i]==' '||linea[i]=='\n') && csum==1){ //SI PUEDO CONTAR Y ENCUENTRO ESPACIO O SALTO DE LINEA, SUMO
            wrdlength++;
            csum = 0;
        } else if(linea[i]!=' ' && linea[i]!='\n'){ //SI VUELVO A ENCONTRAR UN CARACTER PUEDO VOLVER A SUMAR
            csum=1;
        }
    }
    return wrdlength;
}

int linea2argv (char *linea, int argc, char **argv){
    int strlength=strlen(linea);
    int j=0;
    int k=0;
    for(int i=0;i<strlength-1;i++){
        if(linea[i]==' '||linea[i]=='\t'){
            j++;
            k=0;
        }else{
            argv[j][k++]=linea[i];
        }
    }
    return j;
    
}

