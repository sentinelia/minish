#include <string.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

int builtin_cd (int argc, char ** argv){
    
    if(argv[1]==NULL){
        chdir(getenv("HOME"));
    }else if (argv[1]=='-')
    {
        chdir('..');
    }
    else{ 
        chdir(argv[1]);   
    }

}


