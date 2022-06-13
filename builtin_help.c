#include "minish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int builtin_help(int argc, char **argv) {
    if (argc > 2)
    {   //SI TENGO MÁS DE 2 ARGUMENTOS HAGO HELP HELP
        printf("Demasiados argumentos\n");
        printf("%s\n", builtin_lookup("help")->help_txt);
        return EXIT_FAILURE;
    }
    struct builtin_struct *help = builtin_lookup(argv[1]);
    if (help->help_txt != 0) //SI ENCUENTRA COMANDO IMPRIME SU HELP_TEXT
    {
        printf("%s\n", help->help_txt);
        return EXIT_SUCCESS;
    }
    else //SINO HAGO MAN DE ARGUMENTO
    {
        strcpy(argv[0], "man");
        return externo(argc, argv);
    }
}