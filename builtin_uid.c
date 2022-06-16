#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_uid (int argc, char ** argv){

    struct passwd *pws;
    pws = getpwuid(geteuid());

    printf("  nombre de usuario  : %s\n",       pws->pw_name);
    printf("  user ID   : %d\n", (int) pws->pw_uid);
    return EXIT_SUCCESS;

}