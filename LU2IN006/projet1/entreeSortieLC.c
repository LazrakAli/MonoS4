#include "entreeSortieLC.h"
#include <stdio.h>
#include <stdlib.h>

Biblio* charger_n_entrees(char *nomfic, int n){
    FILE *f=fopen(*nomfic,'r');
    if(f==NULL){
        printf("Probleme d'ouverture de fichier!\n");
        exit(1);
    }
    Biblio *B=creer_biblio();
    for(int i=0;i<n;i++){
        int num;
        char titre[150];
        char auteur[150];
        if (fscanf(f,"%d %s %s\n",&num,titre,auteur)!=3){
            printf("Erreur de l'ecture!");
            exit(1);
        }
        inserer_en_tete(B,num,titre,auteur);
    }
    fclose(f);
    return B;
}

void enregistrer_biblio(Biblio *b, char* nomfic){
    FILE *f=fopen(*nomfic,'w');
    if(f==NULL){
        printf("Probleme d'ouverture de fichier!\n");
        exit(1);
    }
    Livre *l=b->L;
    while(l){
        fprintf(f,"%d %s %s",l->num,l->titre,l->auteur);
        l=l->suiv;
    }
}