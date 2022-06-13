#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_pid (int argc, char ** argv){
    printf("%d\n", getpid());
    return EXIT_SUCCESS;
}