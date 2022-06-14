
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>

int builtin_gid (int argc, char ** argv){
    gid_t id = getgid();
    printf("grupo principal: %d\n",id);
    
    gid_t *group;
    int nogroups;
    long ngroups_max;


    ngroups_max = getgroups(0, NULL);
    
    group = (gid_t *)malloc(ngroups_max *sizeof(gid_t));

    nogroups = getgroups(ngroups_max, group);


    
    gid_t *i;

    for(i = group; i < ngroups_max ; i++){
        printf("grupo secundario %s\n", getgrnam(i)->gr_name);
    }

}