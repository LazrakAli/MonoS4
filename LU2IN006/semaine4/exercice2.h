#ifndef _EXERCICE_2_
#define _EXERCICE_2_

#include "exercice2.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct element{
    char *nom;
    struct element *suivant;
}Element;

typedef struct association{
    char *nomAssoc;
    Element *lesMembres;
}Association;

typedef struct Massoc{
    Association *mesAssociations;
    struct Massoc *suivant;
}MaisonDesAssociations;

Association* creerAssociation(char *nom);
void ajouterPersonne(Association *Assoc,Element *elm);
void supprimerPersonne(Association *Assoc,char *nom);
MaisonDesAssociations *creerMaisonAssoc(char *nom);
void ajouterAssociation(MaisonDesAssociations *massoc,Association *assoc);
void supprimerAssociation(MaisonDesAssociations *massoc, Association *assoc);
#endif