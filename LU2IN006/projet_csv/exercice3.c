#include "exercice3.h"
#include <dirent.h>

List* listdir(char* root_dir){
    DIR *dp = opendir (root_dir);
    struct dirent *ep;
    assert(dp != NULL && "Erreur: au niveau de l'ouverture de repertoire");

    List*L =initList();
    while((ep=readdir(root_dir)) =! NULL){
        if ()
    }
}