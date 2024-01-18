#include "biblioLC.h"

Livre*  recherche_num(Biblio* b, int num){
    if (!check_bibli(b))
        return NULL;
    Livre* tmp = b->L;//variable courante temporaire

    while (tmp != NULL){
        if (tmp->num == num){
            printf("Livre %d trouvé\n", num);
            return tmp;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre %d absent\n", num);
    return NULL;
}

Livre*  recherche_titre(Biblio* b, char* titre){
    if (!check_bibli(b))
        return NULL;
    Livre* tmp = b->L;//variable courante temporaire

    while (tmp != NULL){
        if (strcmp(tmp->titre, titre) == 0){
            printf("Livre %s trouvé\n", titre);
            return tmp;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    printf("Livre %s absent\n", titre);
    return NULL;
}

Biblio*  recherche_auteur(Biblio* b, char* auteur){
    if (!check_bibli(b))
        return NULL;
    Biblio* bAuteur = creer_biblio();
    Livre*  tmp = b->L;//variable courante temporaire
    int     nbLivres = 0;

    while (tmp != NULL){
        if (strcmp(tmp->auteur, auteur) == 0){
            inserer_en_tete(bAuteur,tmp->num,tmp->titre,auteur);
            nbLivres++;
        }
        tmp = tmp->suiv;//on prend le suivant et on réitère
    }
    if (nbLivres == 0){ //si aucun livre de auteur trouvé on libere la biblio vide
        printf("Livre ecrit par %s absent\n", auteur);
        liberer_biblio(bAuteur);
        return NULL;
    }
    printf("Livre de %s = %d\n", auteur, nbLivres);
    return bAuteur;
}

Biblio* recherche_duplicata(Biblio* b, char* titre, char* auteur){
    Biblio* bb = creer_biblio();//creation de la bibliothèque de retour
    Livre* tmp = b->L;//variable courante temporaire
    
    while(tmp){
        if ((strcmp(auteur,tmp->auteur) == 0) && (strcmp(titre,tmp->titre) == 0))
            inserer_en_tete(bb, tmp->num, tmp->titre, tmp->auteur);//si  titre et l'auteur indentique on ajoute le livre dans notre bibliothèque de retour
        tmp = tmp->suiv;//livre suivant
    }
    return bb;//retour de la bibliothèque de retour
}