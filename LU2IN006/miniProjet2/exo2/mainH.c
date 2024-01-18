#include "biblioH.h"
#include "entreeSortieH.h"

static void  testAffichage(BiblioH* b){
  printf("Test Affichage:\n");
  afficher_biblioH(b);
}

static void  testRecherche(BiblioH* b){
  printf("\nRecherche par numero:\n");
  afficher_livreH(recherche_numH(b, 48));
  afficher_livreH(recherche_numH(b, 5045));

  printf("\nRecherche par titre:\n");   
  afficher_livreH(recherche_titreH(b, "testons"));
  afficher_livreH(recherche_titreH(b, "SOFS"));

  printf("\nRecherche par auteur:\n");   
  afficher_biblioH(recherche_auteurH(b, "VH"));
  afficher_biblioH(recherche_auteurH(b, "hapj"));
}

void  testSupprime(BiblioH* b){
  // faire avec des petite biblio pour etre lisible
  printf("\nSupprime par titre:\n");   
  afficher_biblioH(b);
  supprime_titreH(b,"testons");
  supprime_titreH(b,"WPQCA");
  afficher_biblioH(b);

  printf("\nSupprime par auteur:\n");   
  afficher_biblioH(b);
  supprime_auteurH(b,"VH");
  supprime_auteurH(b,"adrr");
  afficher_biblioH(b);
}

void  testFusion(char **av){
  BiblioH *b1 = charger_n_entreesH(av[1], atoi(av[2]));
  BiblioH *b2 = charger_n_entreesH(av[1], atoi(av[2]));
  printf("biblio a dupliquer:\n");
  afficher_biblioH(b1);
  printf("\n\nbiblio dupliquer:\n");
  fusion_biblioH(b1, b2);
  afficher_biblioH(b1);
  liberer_biblioH(b1);
}

int main(int ac, char **av){
  if (check_arg(ac, av) != 0) //verifie si argument valides
    return -1;
  BiblioH *b = charger_n_entreesH(av[1], atoi(av[2]));

  testAffichage(b);
  testRecherche(b);
  testSupprime(b);
  testFusion(av);

  liberer_biblioH(b);
  return 0;
}