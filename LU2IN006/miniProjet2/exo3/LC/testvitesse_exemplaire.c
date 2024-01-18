#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <limits.h>
#include <time.h>

void test_taille(FILE *data, FILE* ecriture,int n,char * titre, char* auteur){
    unsigned long temps_initial;
    unsigned long temps_final;
    double temps_cpu_1;
    Biblio *bh = charger_n_entrees(data, n);
    temps_initial = clock();
    Biblio *br = recherche_tous_livres_Exemplaire(bh,titre,auteur);
    temps_final = clock();
    temps_cpu_1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    fprintf(ecriture, "%d %f \n", n, temps_cpu_1);

    liberer_biblio(bh);
    liberer_biblio(br);

}

int main(int argc, char **argv){
    srand(time(NULL));
    FILE *fecriture = fopen("data.txt", "w");
    FILE *fdata = fopen("GdeBiblio.txt", "r");
    for(int i = 1000 ; i < 5000 ; i=i+100)
        test_taille(fdata, fecriture, i,argv[3],argv[4]);

    fclose(fdata);
    fclose(fecriture);
    return 0;
}
