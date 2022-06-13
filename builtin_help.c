#include "minish.h"
#include <stdio.h>

int builtin_help (int argc, char ** argv){
    if(argc>2){
        printf("Demasiados argumentos\n");
        return -1;
    }
    struct builtin_struct *help = builtin_lookup(argv[1]);
    if(help->help_txt!=0){
        printf("%s\n", help->help_txt);
    } else {
        printf("lol\n");
        return externo(argc, argv);
    }
}