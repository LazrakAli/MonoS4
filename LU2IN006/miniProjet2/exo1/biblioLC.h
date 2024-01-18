#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct livre{
  int   num;
  char* titre;
  char* auteur;
  struct livre* suiv;
}       Livre;

typedef struct { /* Tete fictive */
  Livre*    L; /* Premier element */
}       Biblio;

//utils.c
int     check_arg(int ac, char **av);
int     check_bibli(Biblio* b);
void    menu();
void    menuCreationBiblio();
void    menuRecherche();
void    menuSupprime();


//biblioLC.c - creation et insertion
Livre*  creer_livre(int num, char* titre, char* auteur);
Biblio* creer_biblio();
void    inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);

//liberer.c
void    liberer_livre(Livre* l);
void    liberer_biblio(Biblio* b);

//affichage.c
void    afficher_livre(Livre* l);
void    afficher_biblio(Biblio* b);

//recherche.c
Livre*  recherche_num(Biblio* b, int num);
Livre*  recherche_titre(Biblio* b, char* titre);
Biblio* recherche_auteur(Biblio* b, char* auteur);
Biblio* recherche_duplicata(Biblio* b, char* titre, char* auteur);

//supprime.c
void    supprime_num(Biblio* b, int num);
void    supprime_titre(Biblio* b, char* titre);
void    supprime_auteur(Biblio* b, char* auteur);

//fusion.c
Biblio* fusion_biblio(Biblio* b1, Biblio* b2);

#endif