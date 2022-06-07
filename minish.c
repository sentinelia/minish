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
#include "liena2argv.h"


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
    struct sigaction oldact, newact;
    
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

        if (strncmp(line, "sleep", 5) == 0) { 
            // very bad technique, only for demo purposes
            // will fork a child to run date command

            pid_t pid;                          // process ID: an unsigned integer type
            int wait_status;                    // wait status will be filled by waitpid syscall

            fprintf(stderr, "Will fork sleep command\n");

            sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
            newact = oldact;

            if ((pid = fork()) < 0) {           // fork error, i.e. too many processes
                err(0, "fork error\n"); // will fprintf the error and go on
            }

            else if (pid == 0) {                 // child process
                
                // ============== NEW CODE HERE ==============
                newact.sa_handler = SIG_DFL;
                sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child

                execlp("sleep", "sleep", "5", NULL);    // if successful, child will go on with new executable
                err(EXIT_FAILURE, "execvp error\n"); // if exec not successful, just exit child
            }

            else {                               // pid > 0: parent (shell) process

                // ============== NEW CODE HERE ==============
                newact.sa_handler = SIG_IGN;
                sigaction(SIGINT, &newact, NULL);   // ignore SIGINT while waiting

                waitpid(pid, &wait_status, 0);

                // ============== NEW CODE HERE ==============
                sigaction(SIGINT, &oldact, NULL);   // restore SIGINT when child finishes

                fprintf(stderr, "Ended sleep child process\n");

                // do something with wait_status
            }
        }
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}

// IMPLEMENTAR BUILTINS ACÁ
// LINEA2ARGV QUEDA EN ARCHIVO APARTE
