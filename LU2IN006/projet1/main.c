#include <stdio.h>
#include <stdlib.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <nomfic> <n>\n", argv[0]);
        return 1;
    }
    char* nomfic = argv[1];
    int n = atoi(argv[2]);
    Biblio* b = charger_n_entrees(nomfic, n);
    afficher_biblio(b);
    liberer_biblio(b);
    return 0;
}
