#include "biblioH.h"


void liberer_livreH(LivreH* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}


void liberer_biblioH(BiblioH *b){
    LivreH* tmp = NULL;
    
    for (int i = 0; i < b->m; i++){
       tmp = b->T[i];
       while(tmp != NULL){
           b->T[i] = b->T[i]->suiv;
           liberer_livreH(tmp);
           tmp = b->T[i];
       }
    }
    free(b->T);
    free(b);
}
