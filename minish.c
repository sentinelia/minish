// minish - v5 - catch signals on the main loop, completed

#include "minish.h"
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void prompt(char *ps)
{
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

//LIBERA LUGARES DE MEMORIA DE ARRAY DE PALABRAS
void liberar_array(char **arr, int size){
    for(int i = 0;i<size;i++){
        free(arr[i]);
    }
    free(arr);
}

// ============== NEW CODE HERE ==============
void sigint_handler(int signum)
{ // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

int STATUS;
char pwd[MAXCWD];
// NO SE QUE HACE LA MITAD DE LAS COSAS QUE ESTÁN ACÁ
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    char *progname = argv[0];
    struct sigaction oldact, newact;
    char **args;
    struct linkedlist *history;
    FILE* minish_history;

    //minish_history=fopen('minish_history.txt','at');

    sigaction(SIGINT, NULL,
              &newact); // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL); // set SIGINT handler for loop
    getcwd(pwd, MAXCWD);

    for (;;)
    {
        prompt(pwd);
        if (fgets(line, MAXLINE, stdin) == NULL)
        { // EOF
            // ============== NEW CODE HERE ==============
            if (feof(stdin))
            {
                break; // normal EOF, break loop
            }
            else
            {
                continue; // not EOF, read system call was interrupted, continue
                          // loop
            }
        }

        struct node *newcmd;
        newcmd = malloc(sizeof(struct node));
        newcmd->cmd = line;
        newcmd->anterior=history->ultimo;
        history->ultimo=newcmd;
        history->listsize+=1;

        args = malloc(sizeof(char *) * MAXWORDS);
        for (int i = 0; i < MAXWORDS; i++)
        {
            args[i] = malloc(sizeof(char) * MAXLINE);
        }

        char argq = linea2argv(line, MAXLINE, args); //CANTIDAD DE ARGUMENTOS

        if (argq != 0)
        {
            STATUS = ejecutar(argq, args); //EJECUTO COMANDO QUE SE ENCUENTRA EN ARGS[0], CON ARGQ CANTIDAD DE ELEMENTOS
        }
        liberar_array(args, MAXWORDS);
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}
