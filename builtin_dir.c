#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <grp.h>

//FUNCIÓN QUE FORMATEA LOS PERMISOS PARA QUE SEA LEGIBLE
char *format_ch(int mode, char trwx[11]){
    //STRING QUE INDICA LOS PERMISOS Y TIPO DE ARCHIVO
    switch (mode & S_IFMT)
    {
    case S_IFDIR:
        trwx[0] = 'd';
        break;
    case S_IFBLK:
        trwx[0] = 'b';
        break;
    case S_IFCHR:
        trwx[0] = 'c';
        break;
    case S_IFIFO:
        trwx[0] = 'p';
        break;
    case S_IFLNK:
        trwx[0] = 'l';
        break;
    case S_IFSOCK:
        trwx[0] = 's';
        break;
    case S_IFREG:
        trwx[0] = '-';
        break;
    default:
        trwx[0] = 'S';
    }
    trwx[1] = (mode & S_IRWXU) & S_IRUSR ? 'r':'-';
    trwx[2] = (mode & S_IRWXU) & S_IWUSR ? 'w':'-';
    trwx[3] = (mode & S_IRWXU) & S_IXUSR ? 'x':'-';
    trwx[4] = (mode & S_IWGRP) & S_IRGRP ? 'r':'-';
    trwx[5] = (mode & S_IWGRP) & S_IWGRP ? 'w':'-';
    trwx[6] = (mode & S_IWGRP) & S_IXGRP ? 'x':'-';
    trwx[7] = (mode & S_IRWXO) & S_IROTH ? 'r':'-';
    trwx[8] = (mode & S_IRWXO) & S_IWOTH ? 'w':'-';
    trwx[9] = (mode & S_IRWXO) & S_IXOTH ? 'x':'-';
    trwx[10] = '\0';

    return trwx;
}
//ESTA FUNCIÓN TRANSFORMA TIME_T EN STRING
char* formatdate(char* str, time_t val)
{       
        
        strftime(str, 20, "%d/%m/%Y %H:%M:%S", localtime(&val));
        return str;
}

int builtin_dir (int argc, char ** argv){
    DIR *dir;
    struct dirent *myfile;
    struct stat mystat;
    char trwx[11]; //STRING PERMISOS
    char time[20]; //STRING FECHA DE CREACIÓN

    if(argc==1){
        dir = opendir(".");
    } else {
        dir = opendir(argv[1]);
    }
    
    //FUNCION READDIR VA LEYENDO DE A UN DIRECTORIO
    //LUEGO IMPRIMO INFORMACIÓN FORMATEADA SOBRE EL MISMO
    while((myfile = readdir(dir)) != NULL)
    {
        stat(myfile->d_name, &mystat);
        printf("%s", format_ch(mystat.st_mode, trwx));
        printf(" %d", mystat.st_nlink);
        printf(" %s", getgrgid(mystat.st_gid)->gr_name); //TRANSFORMAR
        printf(" %s", getpwuid(mystat.st_gid)->pw_name); //TRANSFORMAR
        printf("\t%d",mystat.st_size);
        printf("\t%s",formatdate(time, mystat.st_ctime));
        printf("\t%s\n", myfile->d_name);
    }
    closedir(dir);
    return 0;
}

