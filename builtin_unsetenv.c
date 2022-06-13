#include <stdio.h>
#include <stdlib.h>


int builtin_unsetenv (int argc, char ** argv){
    for (int i = 1; i < argc; i++)
    {
        unsetenv(argv[i]); //BASTANTE STRAIGHT FORWARD LA VERDAD
    }
    return EXIT_SUCCESS;
}
