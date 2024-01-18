#include "biblioLC.h"

void    liberer_livre(Livre* l){
    if (l == NULL)//verif si le livre existe
        return;
    free(l->titre);//suppression titre alloue
    free(l->auteur);//suppression auteur alloue
    free(l);//suppression livre alloue
}

void    liberer_biblio(Biblio* b){
    if (b == NULL)//verif si biblio existe
        return;
    
    Livre*  tmp = b->L;//valeur temporaire pour supprimer livre courant
    while (tmp != NULL){
        b->L = b->L->suiv;
        liberer_livre(tmp);
        tmp = b->L;
    }
    free(b);
}