#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // use sqrt
#include <ctype.h> // pour utiliser isalpha

typedef struct livreh{
  int   clef;
  int   num;
  char* titre;
  char* auteur;
  struct livreh* suiv;
}       LivreH;

typedef struct table {
  int       nE; /*nombre d’elements contenus dans la table de hachage */
  int       m; /*taille de la table de hachage */
  LivreH**  T; /*table de hachage avec resolution des collisions par chainage */
}       BiblioH;


//utils.c
int       check_arg(int ac, char **av);
int       check_bibliH(BiblioH* b);

//biblioH.c - gestion/creation et insertion
int       fonctionClef(char *auteur);
int       fonctionHachage(int cle, int m);
LivreH*   creer_livreH(int num, char* titre, char* auteur);
BiblioH*  creer_biblioH(int m);
void      inserer(BiblioH* b, int num, char* titre, char* auteur);

//libererH.c
void    liberer_livreH(LivreH* l);
void    liberer_biblioH(BiblioH* b);

//affichageH.c
void    afficher_livreH(LivreH* l);
void    afficher_biblioH(BiblioH* b);

// //rechercheH.c
LivreH*  recherche_numH(BiblioH* b, int num);
LivreH*  recherche_titreH(BiblioH* b, char* titre);
BiblioH* recherche_auteurH(BiblioH* b, char* auteur);
BiblioH* recherche_duplicataH(BiblioH* b, char* titre, char* auteur);

// //supprimeH.c
void    supprime_titreH(BiblioH* b, char* titre);
void    supprime_auteurH(BiblioH* b, char* auteur);
void    supprime_numTitreAuteur(BiblioH* b,int num,char* titre,char* auteur);

// //fusionH.c
BiblioH* fusion_biblioH(BiblioH* b1, BiblioH* b2);

#endif
