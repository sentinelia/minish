#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>

//FUNCIÓN QUE FORMATEA LOS PERMISOS PARA QUE SEA LEGIBLE
char format_ch(int mode){
    char trwx[2]; //STRING QUE INDICA LOS PERMISOS Y TIPO DE ARCHIVO
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
        return "ni idea";
        break;
    }
    trwx[1] = '\0';
    return trwx[0];
}

int builtin_dir (int argc, char ** argv){
    DIR *dir;
    struct dirent *myfile;
    struct stat mystat;

    if(argc==1){
        dir = opendir(".");
    } else {
        dir = opendir(argv[1]);
    }

    while((myfile = readdir(dir)) != NULL)
    {
        stat(myfile->d_name, &mystat);    
        printf("%d",mystat.st_size);
        printf("\t%c", format_ch(mystat.st_mode));
        printf("\t%s", getpwuid(mystat.st_uid)->pw_name); //TRANSFORMAR
        printf("\t%s\n", myfile->d_name);
    }
    closedir(dir);
}

