#include "minish.h"
#include <stdio.h>
int builtin_status (int argc, char ** argv){
    fprintf(stdout,"%d\n", STATUS);
    return STATUS;
}