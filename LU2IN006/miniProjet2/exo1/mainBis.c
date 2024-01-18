#include "biblioLC.h"
#include "entreeSortieLC.h"


void  testAffichage(Biblio* b){
  printf("Test Affichage:\n");
  afficher_biblio(b);
}

void  testRecherche(Biblio* b){
  printf("\nRecherche par numero:\n");
  recherche_num(b,48);
  recherche_num(b,5045);

  printf("\nRecherche par titre:\n");   
  recherche_titre(b,"testons");
  recherche_titre(b,"SOFS");

  printf("\nRecherche par auteur:\n");   
  afficher_biblio(recherche_auteur(b,"VH"));
  afficher_biblio(recherche_auteur(b,"hapj"));
}

void  testSupprime(Biblio* b){
  //faire avec des petite biblio pour etre lisible
  printf("\nSupprime par numero:\n");
  afficher_biblio(b);
  supprime_num(b,1);
  supprime_num(b,11);
  afficher_biblio(b);

  printf("\nSupprime par titre:\n");   
  afficher_biblio(b);
  supprime_titre(b,"testons");
  supprime_titre(b,"SOFS");
  afficher_biblio(b);

  printf("\nSupprime par auteur:\n");   
  afficher_biblio(b);
  supprime_auteur(b,"VH");
  supprime_auteur(b,"adrr");
  afficher_biblio(b);
}

void  testFusion(char **av){
  Biblio *b1 = charger_n_entrees(av[1], atoi(av[2]));
  Biblio *b2 = charger_n_entrees(av[1], atoi(av[2]));

  fusion_biblio(b1, b2);
  afficher_biblio(b1);
  liberer_biblio(b1);
}

int main(int ac, char **av){
  if (check_arg(ac, av) != 0) //verifie si argument valides
    return -1;
  Biblio *b = charger_n_entrees(av[1], atoi(av[2]));


  testAffichage(b);
  testRecherche(b);
  testSupprime(b);
  testFusion(av);

  liberer_biblio(b);
  return 0;
}