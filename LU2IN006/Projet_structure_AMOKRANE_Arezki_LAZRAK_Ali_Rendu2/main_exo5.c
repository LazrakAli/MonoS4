#include "exo6.h"
#include "exo5.h"
#include "exo3.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exo2.h"
#include "exo1.h"
int main(){
    generate_random_data(17,4);
    CellKey *vt=read_public_keys("keys.txt"); // lecture dans le fichier les clés
    CellKey *candi=read_public_keys("candidates.txt"); // lecture dans le fichier les candidates 
    HashCell *cell=create_hashcell(vt->data);
    int sizeV=48;
    int sizeC=18;
    CellProtected *decl=valid_list_protected(read_protected("declarations.txt"));
    Key *winner=compute_winner(decl,candi,vt,sizeC,sizeV); // définir le gagnant 
    char *winnerstr=key_to_str(winner);
    printf("Le gagnant est  : %s\n",winnerstr);

    // Libération des éléments créé
    delete_list_protected(decl);
    delete_list_keys(vt);
    delete_list_keys(candi);
    free(cell);
    free(winner);
    free(winnerstr);
    return 0;
}

