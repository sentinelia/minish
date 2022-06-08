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


// NO SE QUE HACE LA MITAD DE LAS COSAS QUE ESTÁN ACÁ
int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    
    
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

        ejecutar(argc, argv);

    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}

// AL FINAL BUILT INS TAMBIÉN VAN EN ARCHIVO SEPARADO
// LA DIFERENCIA ES QUE LOS BUILTIN SON FUNCIONES EN .C,
// LOS COMANDOS EXTERNOS SE LLAMAN CON EXCECVP
