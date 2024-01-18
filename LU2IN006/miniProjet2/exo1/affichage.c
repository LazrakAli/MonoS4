#include "biblioLC.h"

void    afficher_livre(Livre* l){
    if (l == NULL)
        printf("Livre inexistant\n");//si le livre est NULL alors on le signal
    else
        printf("Livre : Numero : %d - Titre : %s - Auteur : %s\n", l->num, l->titre, l->auteur);//affichage des champs du livre
}

void    afficher_biblio(Biblio* b){
    if (b == NULL || b->L == NULL){
        printf("Biliotheque %s.\n", b == NULL ? "inexistante" : "vide");
        return;
    }
    Livre* tmp = b->L;//variable courante temporaire

    while (tmp != NULL){
        afficher_livre(tmp);//affichage du livre courant
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
}
