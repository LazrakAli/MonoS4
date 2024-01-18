#include "entreeSortieH.h"

//return biblio vide si n <= 0
BiblioH  *charger_n_entreesH(char* nomfic, int n){
    BiblioH* b = creer_biblioH(n);
    FILE* f;
    int num;
    char titre[256];
    char auteur[256];
    char ligne[256];
    int i = 0;

    if (!(f = fopen(nomfic, "r"))){
        printf("Erreur Ouverture fichier : charger_n_entreesH(%s, %d)\n", nomfic, n);
        return NULL;
    }
    while (i < n && fgets(ligne, 256, f)){
        if (sscanf(ligne,"%d %s %s", &num, titre, auteur) != 3)
            printf("Line %d - Reading error : charger_n_entreesH(%s, %d)\n",i, nomfic, n);
        inserer(b, num, titre, auteur);
        i++;
    }
    fclose(f);
    return b;
}

void    enregistrer_biblio(BiblioH* b, char* nomfic){
    if (b == NULL)
        return;
    LivreH* l;
    int     i = 0;
    FILE*   f;

    if (!(f = fopen(nomfic, "w"))){
        printf("Erreur Ouverture fichier : enregistrer_biblio(bibli, %s)\n", nomfic);
        return ;
    }
    while (i < b->m){
        l = b->T[i];
        while(l != NULL){
            fprintf(f,"%d %s %s\n", l->num, l->titre, l->auteur);
            l = l->suiv;
        }
        i++;
    }
    fclose(f);
}