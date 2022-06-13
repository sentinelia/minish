#include <unistd.h>
#include <stdio.h>

int builtin_pid (int argc, char ** argv){
    printf("%d\n", getpid());
    return 0;
}