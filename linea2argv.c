#include <string.h>

int linea2argv (char *linea, int argc, char **argv){
    int strlength=strlen(linea);
    int j=0;
    int k=0;
    for(int i=0;i<strlength;i++){
        if(linea[i]==' '||linea[i]=='\t'){
            j++;
            k=0;
        }else{
            argv[j][k++]=linea[i];
        }

    }
    return j;
    
}