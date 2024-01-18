#include "biblioLC.h"
#include "entreeSortieLC.h"
#define NB_MAX_BIBLIO 10

static void    cas1(int nbBiblio, Biblio *b[NB_MAX_BIBLIO]){
    if (nbBiblio == 0)
        printf("Aucune bibliotheque n'est créé.\n");
    else{
        printf("Il y a %d bibliotheques laquelle voulez vous afficher?(0-%d)\n", nbBiblio, nbBiblio - 1);
        char ligne[256];
        int choix;
        fgets(ligne, 256, stdin);
        if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix >= nbBiblio){
            printf("%s - cas1\n", (choix < 0 || choix >= nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
            cas1(nbBiblio, b); //appel recursif tant que le choix est invalide
        } else 
            afficher_biblio(b[choix]);
    }
}

static void    cas2(int *nbBiblio, Biblio* b[NB_MAX_BIBLIO]){
    if (*nbBiblio == NB_MAX_BIBLIO){
        printf("Le nombre maximum de bibliotheque est atteint veuillez en supprimer une.\n");
        return;
    }
    char ligne[256];
    int choix;

    menuCreationBiblio();
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix > 2){
        printf("%s - cas2\n", (choix < 0 || choix > 2) ? "Choix invalide." : "Erreur format.");
        return; //retour menu si choix est invalide
    }
    if (choix == 1){
        printf("Bibliotheque vide créé\n");
        b[*nbBiblio] = creer_biblio();
        *nbBiblio += 1;
        return;
    } else if  (choix == 2){
        printf("Indiquez : <nom_fichier> <nombre_lignes_lire>\n");
        char file[256];
        int nbLignes;
        
        fgets(ligne, 256, stdin);
        if (sscanf(ligne, "%s %d", file, &nbLignes) != 2){//si argument
            printf("Invalid format Usage: <nom_fichier> <nombre_lignes_lire>\n");
            printf("Bibliotheque vide créé\n");
            b[*nbBiblio] = creer_biblio();
        }else
            b[*nbBiblio] = charger_n_entrees(file, nbLignes);
        *nbBiblio += 1;
    }
}

static void    cas3(int nbBiblio, Biblio* b[NB_MAX_BIBLIO]){
    int     choixB;
    char    ligne[256];
    int     num;
    char    choix_titre[256];
    char    choix_auteur[256];

    if (nbBiblio == 0){
        printf("Il n'existe pas de bibliotheque. Veuillez en creer une pour inserer un livre\n");
        return;
    }
    printf("Inserer un livre dans une bibliotheque\n");
    
    printf("Il y a %d bibliotheques dans laquelle voulez vous supprimer un livre?(0-%d)\n", nbBiblio, nbBiblio - 1);
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choixB) != 1 || choixB < 0 || choixB >= nbBiblio){
        printf("%s - cas3\n", (choixB < 0 || choixB >= nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
        return;
    }
    printf("Format : <num> <titre> <auteur>\n");
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d %s %s", &num, choix_titre, choix_auteur) != 3 || num < 0){
        printf("Erreur format\n");
        return;
    }
    inserer_en_tete(b[choixB], num, choix_titre, choix_auteur);// on inserer_en_tete le livre crée dans la bibliothèque voulu
    printf("Livre a ete ajouter !\n");  
}

static void    cas4(int nbBiblio, Biblio* b[NB_MAX_BIBLIO]){
    if (nbBiblio == 0){
        printf("Recherche impossible : Aucune bibliotheque n'est créé.\n");
        return;
    }
    char ligne[256];
    int choix;
    int choixB;
    menuRecherche();

    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix > 4){
        printf("%s - cas4\n", (choix < 0 || choix > 4) ? "Choix incorrect." : "Erreur format.");
        cas4(nbBiblio, b); //appel recursif tant que le choix est invalide
    }
    printf("Il y a %d bibliotheques dans laquelles voulez vous chercher?(0-%d)\n", nbBiblio, nbBiblio - 1);
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choixB) != 1 || choixB < 0 || choixB >= nbBiblio){
        printf("%s - cas4\n", (choixB < 0 || choixB >= nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
        return;
    }
    if (choix == 1){
        int num;
        printf("Numero de Livre a chercher :\n");
        fgets(ligne, 256, stdin);
        sscanf(ligne, "%d", &num);
        afficher_livre(recherche_num(b[choixB], num));
    } else if (choix == 2 || choix == 3){
        printf("%s a chercher :\n", choix == 2? "Titre" : "Auteur");
        fgets(ligne, 256, stdin);
        char str[256];
        sscanf(ligne, "%s", str);
        choix == 2 ? afficher_livre(recherche_titre(b[choixB], str)) : afficher_biblio(recherche_auteur(b[choixB], str));
    }
}

static void    cas5(int *nbBiblio, Biblio* b[NB_MAX_BIBLIO]){
    if (nbBiblio == 0){
        printf("Suppression impossible : Aucune bibliotheque n'est créé.\n");
        return;
    }
    menuSupprime();
    char ligne[256];
    int choix;

    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix > 4){
        printf("%s - cas5\n", (choix < 0 || choix > 4) ? "Choix incorrect." : "Erreur format.");
        return; //retour menu si choix est invalide
    } 
    if (choix == 1){//sup. une biblio
        printf("Il y a %d bibliotheques laquelle voulez vous supprimer?(0-%d)\n", *nbBiblio, *nbBiblio - 1);
        fgets(ligne, 256, stdin);
        if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix >= *nbBiblio){
            printf("%s - cas5\n", (choix < 0 || choix >= *nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
            return;
        }
        liberer_biblio(b[choix]);
        int i = choix;
        while (i < NB_MAX_BIBLIO){
            b[i] = b[i+1];
            i++;
        }
        b[NB_MAX_BIBLIO - 1] = NULL;
        *nbBiblio -= 1;
    } else if (choix > 1){
        printf("Il y a %d bibliotheques dans laquelle voulez vous supprimer un livre?(0-%d)\n", *nbBiblio, *nbBiblio - 1);
        int choixB;
        fgets(ligne, 256, stdin);
        sscanf(ligne, "%d", &choixB);
        if (sscanf(ligne, "%d", &choixB) != 1 || choixB < 0 || choixB > *nbBiblio){
            printf("%s - cas5\n", (choixB < 0 || choixB > *nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
            return;
        }
        if (choix == 2){
            printf("Numero de Livre a supprimer :\n");
            fgets(ligne, 256, stdin);
            int num;
            sscanf(ligne, "%d", &num);
            supprime_num(b[choixB], num);
        } else if (choix == 3 || choix == 4){
            printf("%s a supprimer :\n", choix == 3? "Titre" : "Auteur");
            fgets(ligne, 256, stdin);
            char str[256];
            sscanf(ligne, "%s", str);
            choix == 3 ? supprime_titre(b[choixB], str) : supprime_auteur(b[choixB], str);
        }
    } 
}

static void    cas6(int *nbBiblio, Biblio* b[NB_MAX_BIBLIO]){
    if (*nbBiblio < 2){
        printf("Fusion impossible : Nombre de bibliotheques insufisant.\n");
        return;
    }
    char ligne[256];
    int b1, b2;

    printf("Il y a %d bibliotheques dans lesquelles voulez vous fusionner?(0-%d)\n", *nbBiblio, *nbBiblio - 1);
    printf("Format : <num_b1> <num_b2>\n");
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d %d", &b1, &b2) != 2 || b1 < 0 || b2 < 0 || b1 >= *nbBiblio || b2 >= *nbBiblio){
        printf("%s - cas6\n", (b1 < 0 || b2 < 0 || b1 >= *nbBiblio || b2 >= *nbBiblio) ? "Numero de bibliotheques incorrect." : "Erreur format.");
        cas6(nbBiblio, b); //appel recursif tant que le choix est invalide
    }
    if (b1 == b2){
        printf("Fusion de la meme bibliotheque impossible");
        return;
    }
    fusion_biblio(b[b1], b[b2]);
    int i = b2;
    while (i < NB_MAX_BIBLIO){//decale toute la liste de biblio 
        b[i] = b[i + 1];
        i++;
    }
    b[NB_MAX_BIBLIO - 1] = NULL;
    *nbBiblio -= 1;
}

static void    cas7(int nbBiblio, Biblio *b[NB_MAX_BIBLIO]){
    if (nbBiblio == 0){
        printf("Aucune bibliotheque n'est créé.\n");
        return;
    }
    printf("Il y a %d bibliotheques laquelle voulez vous enregistrer?(0-%d)\n", nbBiblio, nbBiblio - 1);
    char ligne[256];
    int choix;
    fgets(ligne, 256, stdin);
    if (sscanf(ligne, "%d", &choix) != 1 || choix < 0 || choix >= nbBiblio){
        printf("%s - cas7\n", (choix < 0 || choix >= nbBiblio) ? "Numero de bibliotheque incorrect." : "Erreur format.");
        cas7(nbBiblio, b); //appel recursif tant que le choix est invalide
    } else {
        char nomFic[256];
        printf("Donnez le nom du fichier dans lequel vous voulez l'enregister:\n");
        fgets(ligne, 256, stdin);
        sscanf(ligne, "%s", nomFic);
        enregistrer_biblio(b[choix], nomFic);
        printf("Bibliotheque %d enregistré dans %s\n", choix, nomFic);
    }
}

int main(){
    int choix;
    char ligne[256];
    int nbBiblio = 0;
    Biblio *b[NB_MAX_BIBLIO];
    for (int i = 0; i < NB_MAX_BIBLIO; i++)
        b[i] = NULL;

    do{
        menu();
        printf("\nIl y a actuellement %d bibliotheque\n",nbBiblio);
        fgets(ligne, 256, stdin);
        if (sscanf(ligne, "%d", &choix) != 1){
            printf("Erreur format\n");
            continue;
        }
        switch (choix){
        case 0: //quit
            break;

        case 1://afficher une biblio
            cas1(nbBiblio, b);
            break;

        case 2://creer biblio
            cas2(&nbBiblio, b);//besoin de l'adresse de nb biblio pour mettre a jour le compteur
            break;

        case 3://inserer livre dans une biblio
            cas3(nbBiblio, b);
            break;
        
        case 4: // recherche
            cas4(nbBiblio, b);
            break;

        case 5://suppression
            cas5(&nbBiblio, b);
            break;

        case 6://fusion
            cas6(&nbBiblio, b);
            break;
        
        case 7://enregistrer
            cas7(nbBiblio, b);
            break;

        default:
            printf("Erreur format : main\n");
            break;
        }
    } while (choix != 0);

    while (nbBiblio != 0){
        liberer_biblio(b[nbBiblio - 1]);
        nbBiblio--;
    }
    printf("\nMerci et au revoir!\n");
    return 0;
}