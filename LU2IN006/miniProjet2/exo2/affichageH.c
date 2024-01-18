#include "biblioH.h"

void    afficher_livreH(LivreH* l){
    if (l == NULL)
        printf("Livre inexistant\n");//si le livre est NULL alors on le signal
    else
        printf("Livre : Clef : %d - Numero : %d - Titre : %s - Auteur : %s\n", l->clef, l->num, l->titre, l->auteur);//affichage des champs du livre
}

void    afficher_biblioH(BiblioH* b){
    if (b == NULL ){
        printf("Biliotheque inexistante.\n");
        return;
    }
    int i = 0;
    LivreH* tmp = b->T[i];//variable courante

    while (i < b->m){
        tmp = b->T[i];
        while (tmp != NULL){
            afficher_livreH(tmp);//affichage du livre courant
            tmp = tmp->suiv;
        }
        i++;
    }
}
