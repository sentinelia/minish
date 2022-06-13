
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_gid (int argc, char ** argv){
    
    printf('grupo principal: %s\n',getgid());
    
    gid_t *group;
    int nogroups;
    long ngroups_max;


    ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;
    group = (gid_t *)malloc(ngroups_max *sizeof(gid_t));

    nogroups = getgroups(ngroups_max, group);

    
    
    gid_t *i;
    
    for(i = group; i != NULL; i++){
        printf('grupo secundario %s\n', i);
    }



}