#include "biblioLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Livre* creer_livre(int num,char* titre,char* auteur){
    Livre *l=(Livre *)malloc(sizeof(Livre));
    if(l==NULL){
        printf("Erreur d'allocation memoire!\n");
        exit(1);
    }
    l->num=num;
    l->titre = strndup(titre, 100); 
    l->auteur = strndup(auteur, 100);
    l->suiv=NULL;
    return l;

}

void liberer_livre(Livre* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio *b=(Biblio *)malloc(sizeof(Biblio));
    if(b==NULL){
        printf("Erreur d'allocation memoire!");
        exit(1);
    }
    b->L=NULL;
    return b;    
}

void liberer_biblio(Biblio* b){
    Livre *l=NULL;
    while(b->L){
        l=b->L->suiv;
        liberer_livre(b->L);
        b->L=l;
    }
    free(b);
}
void afficher_biblio(Biblio* b) {
    Livre* l = b->L;
    while (l != NULL) {
        printf("%d %s %s\n", l->num, l->titre, l->auteur);
        l = l->suiv;
    }
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre *l=creer_livre(num,titre,auteur);
    l->suiv=b->L;
    b->L=l;
}
