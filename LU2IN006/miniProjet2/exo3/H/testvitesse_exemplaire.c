#include "biblioH.h"
#include "entreeSortieH.h"
#include <limits.h>
#include <time.h>

void test_taille(FILE *data, FILE* ecriture,int n,char * titre, char* auteur)
{

    unsigned long temps_initial;
    unsigned long temps_final;
    double temps_cpu_1;
    BiblioH *bh = charger_n_entreesH(data, n);
    temps_initial = clock();
    BiblioH *br = recherche_duplicataH(bh,titre,auteur);
    temps_final = clock();
    temps_cpu_1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    fprintf(ecriture, "%d %f \n", n, temps_cpu_1);
    printf("%d \n",n);
    /*affichage_biblio(bh);*/
    affichage_biblioH(br);
    liberer_biblioH(bh);
    liberer_biblioH(br);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    FILE *fecriture = fopen("data.txt", "w");
    FILE *fdata = fopen(argv[1], "r");
    for(int i = 1000 ; i < 5000 ; i=i+100)
        test_taille(fdata, fecriture, i,argv[2],argv[3]);

    fclose(fdata);
    fclose(fecriture);
    return 0;
}
