#ifndef __BIBILIO_LC__
#define __BIBILIO_LC__

typedef struct livre{
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
}Livre;

typedef struct {
    /* Tete fictive*/
    Livre *L;
}Biblio;
void afficher_biblio(Biblio* b);
Livre* creer_livre(int num,char* titre,char* auteur);//creee un livre
void liberer_livre(Livre* l);//Free un livre
Biblio* creer_biblio();//cree une bibliotheque
void liberer_biblio(Biblio* b);//free bibliotheque
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);//ajoute un nouveau livre a la bibliotheque

#endif 