#include "biblioLC.h"

//attention biblio rentree en param doivent etre liberer en dehors
//cree et retourne une biblio qui est la fusion de 2 biblio
Biblio*     fusion_biblio(Biblio* b1, Biblio* b2){
    Livre* tmp = b1->L;//var courante

    while (tmp->suiv)
        tmp = tmp->suiv;//on parcourt b1
    tmp->suiv = b2->L;//dernier livre de b1 sera suivi du premier livre de b2
    b2->L = NULL;//  déréférence le champs de b2
    liberer_biblio(b2);
    return b1;
}
