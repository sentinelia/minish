#include <stdio.h>
#include <stdlib.h>
int builtin_getenv (int argc, char ** argv){
    for(int i = 1; i<argc; i++){
        printf("%s=%s\n", argv[i], getenv(argv[i]));
    }
    return 0;
}