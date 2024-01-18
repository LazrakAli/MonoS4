#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "exercice1.h"

int hashFile(char* source, char* dest){
    char c[1000];
    sprintf(c,"cat %s | sha256sum > %s",source,dest);
    system(c);
}

char* sha256file(char* file){

    static char template[]="/tmp/myfileXXXXXX";

    char fname[1000];
    strcpy(fname,template);
    int fd = mkstemp(fname);
    hashFile(file,fname);

    //recupere la premiere ligne
    char hash[65];
    fgets(hash,65,fd);
    
    //supprime le fichier temporaire
    char cmd[1000];
    sprintf(cmd,"rm %s",fname);
    system(cmd);

    return hash;
}