#include <stdlib.h>
#include <stdio.h>
#define TAILLE 5

void alloue_tableau(int **T,int n){
    int *T=(int *) malloc(n*sizeof(int));
    if (*T == NULL) {
        printf("Erreur d'allocation de mémoire pour le tableau !\n");
        exit(1);
    }
}
void desaloue_tableau(int *T){
    free(T);
}

void remplir_tableau(int *T,int taille,int ValMax){
    for(int i=0;i<taille;i++){
        T[i]=rand()%ValMax;
    }
}

void afficher_tableau(int *T,int taille){
    for(int i=0;i<taille;i++){
        printf("[%d] ",T[i]);
    }
    printf("\n");
}
int main(){
    int *t;
    alloue_tableau(&t,TAILLE);
    remplir_tableau(&t,TAILLE,10);
    afficher_tableau(t,TAILLE);
    desaloue_tableau(t);
    return 0;
}

