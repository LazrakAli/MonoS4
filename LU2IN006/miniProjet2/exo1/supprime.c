#include "biblioLC.h"

void  supprime_num(Biblio* b, int num){
    if (!check_bibli(b))
        return;
    Livre* tmp = b->L, *tmp_sup = b->L;//variable courante et a supprimer

    if (tmp->num == num){//s'il s'agit du premier livre
        b->L = tmp->suiv;
        liberer_livre(tmp_sup);
        return;
    }
    while (tmp->suiv != NULL){
        if (tmp->suiv->num == num){
            tmp_sup = tmp->suiv;
            tmp->suiv = tmp->suiv->suiv;
            liberer_livre(tmp_sup);
            printf("Livre %d supprimé\n", num);
            return ;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre %d absent\n", num);
}

void  supprime_titre(Biblio* b, char* titre){
    if (!check_bibli(b))
        return ;
    Livre* tmp = b->L, *tmp_sup = b->L;//variable courante et a supprimer

    if (strcmp(tmp->titre, titre) == 0){//s'il s'agit du premier livre
        b->L = tmp->suiv;
        liberer_livre(tmp_sup);
        return;
    }
    while (tmp->suiv != NULL){
        if (strcmp(tmp->suiv->titre, titre) == 0){
            tmp_sup = tmp->suiv;
            tmp->suiv = tmp->suiv->suiv;
            liberer_livre(tmp_sup);
            printf("Livre %s supprimé\n", titre);
            return ;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre %s absent\n", titre);
}

void  supprime_auteur(Biblio* b, char* auteur){
    if (!check_bibli(b))
        return ;
    Livre*  tmp = b->L, *tmp_sup = b->L;//variable courante et a supprimer
    int     nbLivres = 0;

    if (strcmp(tmp->auteur, auteur) == 0){//s'il s'agit du premier livre
        b->L = tmp->suiv;
        liberer_livre(tmp_sup);
        nbLivres++;
    }
    while (tmp->suiv != NULL){
        if (strcmp(tmp->suiv->auteur, auteur) == 0){
            tmp_sup = tmp->suiv;
            tmp->suiv = tmp->suiv->suiv;
            liberer_livre(tmp_sup);
            nbLivres++;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre de %s = %d supprimés\n", auteur, nbLivres);
}