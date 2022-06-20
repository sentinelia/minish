#define MAXLINE 1024        // tamaño máximo de la línea de entrada
#define MAXCWD 1024         // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256        // cantidad máxima de palabras en la línea
#define HISTORY_FILE	".minish_history"   // nombre del archivo que almacena historia de comandos
#define MAXHISTORY 500      // tamaño máximo del historial


// Definición de Estructuras

struct builtin_struct {         // struct con información de los builtins
    char *cmd;                  // nombre del comando builtin
    int (*func) (int, char **); // la función que lo ejecuta
    char *help_txt;             // el texto de ayuda
};

struct node{
    char *cmd;
    struct node* anterior; 
};

struct linkedlist{
    struct node *ultimo;
    int listsize;
};

// Variables que deben definirse en el main como externas

extern int globalstatret;	// guarda status del ultimo comando
extern struct sigaction oldact, newact;
extern struct builtin_struct builtin_arr[];
extern char pwd[MAXCWD];
extern int STATUS;
extern struct linkedlist;



/*
    builtin_arr es una lista de los builtins, que se recorrerá en forma lineal.
    Podría usarse una estructura que mejorara la velocidad de búsqueda, pero
    en este ejercicio una lista que se recorre en forma lineal es suficiente.
    Deberá definirse e inicializarse como variable global en el programa principal,
    de esta manera:

    struct builtin_struct builtin_arr[] = {
        { "cd", builtin_cd, HELP_CD },
        .... etc. etc.
        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };
    La definición no puede hacerse en este archivo minish.h porque está pensado
    para ser incluido en todos los fuentes y no se puede definir el mismo array en
    diferentes fuentes de un mismo programa.
*/

/*
    La siguiente lista de constantes de texto puede adaptarse/mejorarse, se pone como ejemplo.
    Lo lógico sería que estuvieran definidas en el mismo fuente que define el array builtin_arr
    en lugar de estar en este archivo .h.
*/


// Funciones a definir en los correspondientes archivos fuentes

extern struct builtin_struct * builtin_lookup(char *cmd);
extern int builtin_exit (int argc, char ** argv);
extern int builtin_help (int argc, char ** argv);
extern int builtin_history (int argc, char ** argv);
extern int builtin_status (int argc, char ** argv);
extern int builtin_cd (int argc, char ** argv);
extern int builtin_dir (int argc, char ** argv);
extern int builtin_getenv (int argc, char ** argv);
extern int builtin_gid (int argc, char ** argv);
extern int builtin_setenv (int argc, char ** argv);
extern int builtin_pid (int argc, char ** argv);
extern int builtin_uid (int argc, char ** argv);
extern int builtin_unsetenv (int argc, char ** argv);
extern int ejecutar (int argc, char ** argv);
extern int externo (int argc, char ** argv);
extern int linea2argv(char *linea, int argc, char **argv);
