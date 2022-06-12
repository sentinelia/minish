// minish - v5 - catch signals on the main loop, completed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "minish.h"

#define MAXLINE 1024
#define MAXWORDS 256



#define HELP_CD       "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR      "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT     "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP     "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY  "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV   "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID      "pid - muestra Process Id del minish"
#define HELP_SETENV   "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS   "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID      "uid - muestra nombre y número de usuario dueño del minish"
#define HELP_GID      "gid - muestra el grupo principal y los grupos secundarios del usuario"
#define HELP_UNSETENV "unsetenv - elimina variables de ambiente"


void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

// ============== NEW CODE HERE ==============
void
sigint_handler(int signum) {                    // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

int liberar_array(char ** arr){
    for(int i = 0; arr[i]!=NULL; i++){
        free(arr[i]);
    }
    free(arr);
    return arr;
}

// NO SE QUE HACE LA MITAD DE LAS COSAS QUE ESTÁN ACÁ
int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    struct sigaction oldact, newact;
    char **args;

    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    
    

    for (;;) {
        prompt(progname);
        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
            // ============== NEW CODE HERE ==============
            if (feof(stdin)) {
                break;      // normal EOF, break loop
            } else {
                continue;   // not EOF, read system call was interrupted, continue loop
            }
        }
        fprintf(stderr, "Will execute command %s", line);
        args = malloc(sizeof(char*) * MAXWORDS);
        for(int i = 0; i<MAXWORDS; i++){
            args[i] = malloc(sizeof(char) * MAXLINE);
        }
        ejecutar(linea2argv(line, MAXLINE, args), args);
        liberar_array(args);
        
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}


// AL FINAL BUILT INS TAMBIÉN VAN EN ARCHIVO SEPARADO
// LA DIFERENCIA ES QUE LOS BUILTIN SON FUNCIONES EN .C,
// LOS COMANDOS EXTERNOS SE LLAMAN CON EXCECVP
