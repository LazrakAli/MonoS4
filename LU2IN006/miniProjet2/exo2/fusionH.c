#include "biblioH.h"

BiblioH*    fusion_biblioH(BiblioH *b1, BiblioH *b2){
    LivreH *tmp; //variable courante temporaire

    for (int i = 0; i < b2->m; i++){
        tmp = b2->T[i];
        while (tmp){
            inserer(b1, tmp->num, tmp->titre, tmp->auteur);
            tmp = tmp->suiv;
        }
    }
    liberer_biblioH(b2);
    return b1;
}