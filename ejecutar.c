#include "minish.h"
#include <stdio.h>
#include <unistd.h>

int ejecutar (int argc, char ** argv){
    struct builtin_struct *built;
    built= builtin_lookup(argv[0]);
    if (built->cmd == 0) {
        printf("not broken yet\n");
        return externo(argc, argv);
    } else {
        return built->func(argc, argv);
    }

}