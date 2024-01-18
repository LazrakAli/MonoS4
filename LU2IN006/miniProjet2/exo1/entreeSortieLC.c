#include "entreeSortieLC.h"

//return biblio vide si n <= 0
Biblio  *charger_n_entrees(char* nomfic, int n){
    FILE* f;
    Biblio* b = creer_biblio();
    int num;
    char titre[256];
    char auteur[256];
    char ligne[256];
    int i = 0;

    if (!(f = fopen(nomfic, "r"))){
        printf("Erreur Ouverture fichier : charger_n_entrees(%s, %d)\n", nomfic, n);
        return NULL;
    }
    while (i < n && fgets(ligne, 256, f)){
        if (sscanf(ligne,"%d %s %s", &num, titre, auteur) != 3)
            printf("Line %d - Reading error : charger_n_entrees(%s, %d)\n",i, nomfic, n);
        inserer_en_tete(b, num, titre, auteur);
        i++;
    }
    fclose(f);
    return b;
}

void    enregistrer_biblio(Biblio* b, char* nomfic){
    if (b == NULL)
        return;
    Livre*  l = b->L;
    FILE*   f;

    if (!(f = fopen(nomfic, "w"))){
        printf("Erreur Ouverture fichier : enregistrer_biblio(bibli, %s)\n", nomfic);
        return ;
    }
    while (l != NULL){
        fprintf(f,"%d %s %s\n", l->num, l->titre, l->auteur);
        l = l->suiv;
    }
    fclose(f);
}