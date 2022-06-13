#include "minish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int builtin_help(int argc, char **argv) {
    if (argc > 2)
    {
        printf("Demasiados argumentos\n");
        return EXIT_FAILURE;
    }
    struct builtin_struct *help = builtin_lookup(argv[1]);
    if (help->help_txt != 0)
    {
        printf("%s\n", help->help_txt);
        return EXIT_SUCCESS;
    }
    else
    {
        strcpy(argv[0], "man");
        return externo(argc, argv);
    }
}