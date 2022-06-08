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

int externo(int argc, char  **argv){
    pid_t pid;                          // process ID: an unsigned integer type
            int wait_status;                    // wait status will be filled by waitpid syscall

            fprintf(stderr, "Will fork sleep command\n");

            sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
            newact = oldact;

            if ((pid = fork()) < 0) {           // fork error, i.e. too many processes
                err(0, "fork error\n"); // will fprintf the error and go on
                return EXIT_FAILURE;
            }

            else if (pid == 0) {                 // child process

                // ============== NEW CODE HERE ==============
                newact.sa_handler = SIG_DFL;
                sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child

                execvp(argv[0], argv);    // if successful, child will go on with new executable
                err(EXIT_FAILURE, "execvp error\n"); // if exec not successful, just exit child
                exit(EXIT_SUCCESS);
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
                return WEXITSTATUS(wait_status);
            }
}