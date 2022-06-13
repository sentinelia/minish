 #include <string.h>
 #include <stdio.h>
 #include "minish.h"
 

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


 struct builtin_struct builtin_arr[] = {
    {"cd", builtin_cd, HELP_CD}, 
    { "exit", builtin_exit, HELP_EXIT },
    { "help", builtin_help, HELP_HELP },
    { "histoy", builtin_history, HELP_HISTORY },
    { "status", builtin_status, HELP_STATUS },
    { "dir", builtin_dir, HELP_DIR },
    { "getenv", builtin_getenv, HELP_GETENV },
    { "gid", builtin_gid, HELP_GID },
    { "setenv", builtin_setenv, HELP_SETENV },
    { "pid", builtin_pid, HELP_PID },
    { "uid", builtin_uid, HELP_UID },
    { "unsetenv", builtin_unsetenv, HELP_UNSETENV },
    { NULL, NULL, NULL}
};

 struct builtin_struct * builtin_lookup(char *cmd){
    struct builtin_struct *p;
    for (p=builtin_arr; p->cmd != NULL; p++) {
        if (strcmp(cmd, p->cmd) == 0) {
          return p;
        }
    }
    return NULL;
 }