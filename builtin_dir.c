#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int builtin_dir (int argc, char ** argv){
    DIR *dir;
    struct dirent *myfile;
    struct stat mystat;

    if(argc==1){
        dir = opendir(".");
    }

    while((myfile = readdir(dir)) != NULL)
    {
        stat(myfile->d_name, &mystat);    
        printf("%d",mystat.st_size);
        printf(" %d %d", mystat.st_uid, mystat.st_flags);
        printf(" %s\n", myfile->d_name);
    }
    closedir(dir);
}