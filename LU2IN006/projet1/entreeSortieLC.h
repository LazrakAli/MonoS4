#ifndef __ENTRE_SORTIE_LC__
#define __ENTRE_SORTIE_LC__

#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n);//permettant de lire n lignes d'un fichier et de les mettre dans une biblio
void enregistrer_biblio(Biblio *b, char* nomfic);//permet de stocker une bibliotheque dans un fichier au bon format(num,titre,auteur)

#endif