#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <limits.h>
#include <time.h>

int main(int argc, char **argv){
  FILE* f = fopen(argv[1],"r");
  unsigned long temps_initial_1;
  unsigned long temps_final_1;
  double temps_cpu_1;
  Biblio* b = charger_n_entrees(f,atoi(argv[2]));

  temps_initial_1 = clock();
  Biblio* bb=recherche_tous_livres_auteur(b,argv[3]);
  temps_final_1 = clock ();
  temps_cpu_1=((double) (temps_final_1 - temps_initial_1)) / CLOCKS_PER_SEC;
  printf("%d %f\n",atoi(argv[4]),temps_cpu_1);
  liberer_biblio(bb);
  liberer_biblio(b);
  fclose(f);
}
