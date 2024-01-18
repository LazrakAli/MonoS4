#include "biblioH.h"


void supprime_numTitreAuteur(BiblioH* b,int num,char* titre,char* auteur){
  int     cle = fonctionHachage(fonctionClef(auteur),b->m);
  LivreH* tmp = b->T[cle];//variable courante temporaire
  LivreH* tmp_supp = b->T[cle];//livre a supprimer

  if((tmp->num == num) && (strcmp(titre, tmp->titre) == 0) && (strcmp(auteur, tmp->auteur) == 0)){
    b->T[cle] = b->T[cle]->suiv;//si le livre a supprimer est le premier alosr on donne le livre en tete de la bibliothèque comme étant le suivant
    liberer_livreH(tmp_supp);//on supprime le premier livre
    b->nE--;
    return ;
  }
  while(tmp){
    if ((tmp->suiv->num == num) && (strcmp(titre,tmp->suiv->titre) == 0) && (strcmp(auteur, tmp->suiv->auteur) == 0)){
        tmp_supp = tmp->suiv;//si le suivant est le livre a supprimer alors on le met dans une variable
        tmp->suiv = tmp->suiv->suiv;//on redéfinit le suivant du livre courant comme étant le suivant du livre à supprimer pour ne pas perdre les informations de la liste
        liberer_livreH(tmp_supp);//on supprimele livre a supprimer
        b->nE--;
        return ;
    }
    tmp = tmp->suiv;//on se déplace dans la liste
  }
}

//supprime le premier livre rencontré avec ce titre
void supprime_titreH(BiblioH *b, char *titre){
    if (!check_bibliH(b))
        return;
    LivreH *tmp = NULL, *tmp_sup = NULL; //variable courante et a supprimer

    for (int i = 0; i < b->m; i++){
        tmp = b->T[i];
        tmp_sup = b->T[i];
        if (tmp && strcmp(tmp->titre, titre) == 0){ //s'il s'agit du premier livre
            b->T[i] = tmp->suiv;
            liberer_livreH(tmp);
            b->nE--;
            printf("Livre %s supprimé\n", titre);
            return;
        }
        while (tmp && tmp->suiv != NULL){
            if (tmp && strcmp(tmp->suiv->titre, titre) == 0){
                tmp_sup = tmp->suiv;
                tmp->suiv = tmp->suiv->suiv;
                liberer_livreH(tmp_sup);
                b->nE--;
                printf("Livre %s supprimé\n", titre);
                return;
            }
            tmp = tmp->suiv; //on prend le suivant et on réitère
        }
    }
    printf("Livre %s absent\n", titre);
}

void  supprime_auteurH(BiblioH* b, char* auteur){
    if (!check_bibliH(b))
        return ;
    int cle = fonctionHachage(fonctionClef(auteur),b->m);
    LivreH*  tmp = b->T[cle], *tmp_sup = NULL;//variable courante et a supprimer
    int     nbLivres = 0;

    while (strcmp(tmp->auteur, auteur) == 0){//s'il s'agit du premier livre
        b->T[cle] = tmp->suiv;
        liberer_livreH(tmp);
        nbLivres++;
    }
    while (tmp->suiv != NULL){
        if (strcmp(tmp->suiv->auteur, auteur) == 0){
            tmp_sup = tmp->suiv;
            tmp->suiv = tmp->suiv->suiv;
            liberer_livreH(tmp_sup);
            nbLivres++;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre de %s = %d supprimés\n", auteur, nbLivres);
}