#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int builtin_uid (int argc, char ** argv){

    struct passwd *pws;
    pws = getpwuid(geteuid());

    if(pws==NULL){
        return -1;
    }else{
        printf("  nombre de usuario  : %s\n",       pws->pw_name);
        printf("  user ID   : %d\n", (int) pws->pw_uid);
        return 0;
    }

}