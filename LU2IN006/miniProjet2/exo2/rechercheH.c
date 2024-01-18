#include "biblioH.h"

LivreH*  recherche_numH(BiblioH* b, int num){
    if (!check_bibliH(b))
        return NULL;
    LivreH* tmp = NULL;
    
    for (int i = 0; i < b->m; i++){
        tmp = b->T[i];
        while(tmp != NULL){
            if (tmp->num == num){
                printf("Livre %d trouvé\n", num);
                return tmp;
            }
            tmp = tmp->suiv;//parcours liste livre de clef i
       }
    }
    printf("Livre %d absent\n", num);
    return NULL;
}

LivreH*  recherche_titreH(BiblioH* b, char *titre){
    if (!check_bibliH(b))
        return NULL;
    LivreH* tmp = NULL;
    
    for (int i = 0; i < b->m; i++){
        tmp = b->T[i];
        while(tmp != NULL){
            if (strcmp(tmp->titre, titre) == 0){
                printf("Livre %s trouvé\n", titre);
                return tmp;
            }
            tmp = tmp->suiv;//parcours liste livre de clef i
       }
    }
    printf("Livre %s absent\n", titre);
    return NULL;
}

BiblioH* recherche_auteurH(BiblioH* b, char* auteur){
    if (!check_bibliH(b))
        return NULL;
    BiblioH* br = creer_biblioH(b->m);//creation de la bibliothèque de retour
    LivreH*  tmp = b->T[fonctionHachage(fonctionClef(auteur), b->m)];//liste de livre avec la clef correspondant a cet auteur
    int      nbLivres = 0;

    while(tmp != NULL){
        if(strcmp(auteur, tmp->auteur) == 0){//si auteur  identique on l'ajoute 
          inserer(br, tmp->num, tmp->titre, tmp->auteur);
          nbLivres++;
        }
        tmp = tmp->suiv;
    }
    if (nbLivres == 0){ //si aucun livre de auteur trouvé on libere la biblio vide
        printf("Livre ecrit par %s absent\n", auteur);
        liberer_biblioH(br);
        return NULL;
    }
    printf("Livre de %s = %d\n", auteur, nbLivres);
    return br;//retour de la bibliothèque de retour
}

BiblioH* recherche_duplicataH(BiblioH* b, char* titre, char* auteur){
    BiblioH* bb = creer_biblioH(b->m);//creation de la bibliothèque de retour
    LivreH* tmp = b->T[fonctionHachage(fonctionClef(auteur), b->m)];//variable courante temporaire

    while(tmp){
        if((strcmp(auteur,tmp->auteur) == 0) && (strcmp(titre,tmp->titre) == 0))
            inserer(bb, tmp->num, tmp->titre, tmp->auteur);//si le titre et l'auteur est le même on ajoute le livre dans notre bibliothèque de retour
        
        tmp = tmp->suiv;//livre suivant
    }
    return bb;//retour de la bibliothèque de retour
}