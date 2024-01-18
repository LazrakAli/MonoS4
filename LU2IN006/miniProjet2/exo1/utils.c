#include "biblioLC.h"

int check_arg(int ac, char **av){
  if (ac != 3 || atoi(av[2]) <= 0){
    printf("Error Usage : ./main <MonFichier> <NombreDeLigne%s>\n", atoi(av[2]) <= 0 ? "(Positif)" : "");
    return -1;
  }
  return 0;
}

//return 0 si biblio vide ou inexistante 0 sinon
int     check_bibli(Biblio* b){
    if (b == NULL || b->L == NULL){
        printf("Biliotheque %s.\n", b == NULL ? "inexistante" : "vide");
        return 0;
    }
    return 1;
}

void    menuSupprime(){
    printf("\nMenu suppression:\n");
    printf("0 - Retour menu principal\n");
    printf("1 - Supprimer une bibliotheque\n");
    printf("2 - Supprimer livre via numero\n");
    printf("3 - Supprimer livre via titre\n");
    printf("4 - Supprimer livre via auteur\n");
}

void    menuRecherche(){
    printf("\nMenu recherche:\n");
    printf("0 - Retour menu principal\n");
    printf("1 - Rechercher un livre via numero\n");
    printf("2 - Rechercher un livre via titre\n");
    printf("3 - Rechercher tous les livres d'un auteur\n");
    // printf("4 - Recherche des ouvrages en plusieurs exemplaires\n");
}

void    menuCreationBiblio(){
    printf("\nMenu creation de bibliotheque:\n");
    printf("0 - Retour menu principal\n");
    printf("1 - Creer une bibliotheque vide\n");
    printf("2 - Creer une bibliotheque a partir d'un fichier\n");
}

void    menu(){
    printf("\n|========================================|\n");
    printf("|                                        |\n");
    printf("|              Menu tme 3                |\n");
    printf("|                                        |\n");
    printf("|========================================|\n");
    printf("\nChoisissez une action (0-12)\n\n");
    printf("0 - Sortie programme\n");
    printf("1 - Afficher une bibliotheque\n");
    printf("2 - Creer une bibliotheque\n");
    printf("3 - Inserer un livre\n");
    printf("4 - Recherche\n");
    printf("5 - Suppression\n");
    printf("6 - Fusion\n");
    printf("7 - Enregister dans un fichier\n");
}