#include "biblioH.h"

int fonctionClef(char *auteur){
    int somme = 0;
    int i = 0;

    while (auteur[i] != '\0'){
        if(isalpha(auteur[i]) == 0)
            printf("Attention le nom de l'auteur '%s' contient des caracteres non alphabetiques!\n", auteur);
        somme += auteur[i];
        i++;
    }
    return somme;
}

int fonctionHachage(int cle, int m){
  double a = (sqrt(5) - 1) / 2;
  return (m * (cle * a - (int)(cle * a)));
}

LivreH *creer_livreH(int num, char *titre, char *auteur){
    LivreH* l; //on crée un livreh

    if (!(l = malloc(sizeof(LivreH)))){//allocation et vérification 
        printf("Erreur de malloc : creer_livre\n"); 
        return NULL;
    }
    //initialisation des champs
    l->clef = fonctionClef(auteur);
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suiv = NULL;
    //fin d'initialisation
    return l; //on retourne le livre crée
}


BiblioH *creer_biblioH(int m){
   BiblioH *b; 
    if (!(b = malloc(sizeof(BiblioH *)))){
        printf("Erreur de malloc : creer_biblio\n"); 
        return NULL;
    }
    b->m = m;
    b->nE = 0;
    if(!(b->T = malloc(m * sizeof(LivreH*)))){
        printf("Erreur de malloc : creer_biblio\n"); 
        return NULL;
    }
    //initialisation des champs
    for(int i = 0; i < b->m; i++)
        b->T[i] = NULL;
    return b; //on retourne la biblio cree
}

void    inserer(BiblioH* b, int num, char* titre, char* auteur){
    if (!b){
        printf("BiblioH n'est pas cree\n");
        return;
    }
    int c = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* l = creer_livreH(num, titre, auteur);
    l->suiv = b->T[c]; 
    b->T[c] = l;
    b->nE++;
}