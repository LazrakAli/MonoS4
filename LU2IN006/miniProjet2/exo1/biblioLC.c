#include "biblioLC.h"

Livre*  creer_livre(int num, char* titre, char* auteur){
    Livre*  l;

    if (!(l = malloc(sizeof(Livre)))){//allocation et verification
        printf("Malloc Error : creer_livre(%d,%s,%s)\n",num, titre, auteur);
        return NULL;
    }
    //initialisation des champs
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suiv = NULL;
    return l;//return livre cree
}


Biblio* creer_biblio(){
    Biblio *b;

    if (!(b = malloc(sizeof(Biblio)))){//allocation et verification
        printf("Malloc Error : creer_biblio()\n");
        return NULL;
    } 
    b->L = NULL;//init champs
    return b;
}


void    inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    Livre*  l = creer_livre(num, titre, auteur);//creation livre
    l->suiv = b->L;
    b->L = l;
}
