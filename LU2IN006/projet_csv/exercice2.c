#include "exercice2.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


//initialise une List
List* initList(){
    List *head=(List*)malloc(sizeof(List));
    *head=NULL;
    return head;
}


//Cree une Cell a partir d'une chaine de charactere
Cell* buildCell(char* ch){
    Cell *cl=(Cell *)malloc(sizeof(Cell));
    assert(cl!=NULL && "Erreur: Allocation de memoire");
    cl->data=strdup(ch);
    assert(cl->data != NULL && "Erreur: Allocation de memoire");
    cl->next=NULL;
    return cl;
}

//Inser la cellule entete de la la liste
void insertFirst(List *L, Cell* C){
    C->next=*L;
    *L=C;
}

//Retourne la chaine de char composant une cellule
char* ctos(Cell* c){
    return c->data;
}

char* ltos(List* L) {
    // Calculer la taille nécessaire pour la chaîne de sortie
    int i = 0;
    Cell* tmp = *L;
    while (tmp) {
        i += strlen(tmp->data) + 1;
        //demande au prof si possible de remplacer strlen par size
        tmp = tmp->next;
    }

    //Allocation de la chaine de sortie
    char* chaineDeSortie = (char*) malloc(i * sizeof(char));
    assert(chaineDeSortie != NULL && "Erreur : Allocation de memoire");

    //Concatene la liste avec séparateurs "|"
    tmp = *L;
    strcat(chaineDeSortie, ctos(tmp));
    tmp = tmp->next;
    while (tmp) {
        strcat(chaineDeSortie, "|");
        strcat(chaineDeSortie, ctos(tmp));
        tmp = tmp->next;
    }
    strcat(chaineDeSortie,"\0"); 
    return chaineDeSortie;
}


Cell* listGet(List* L, int i) {
    Cell* tmp = *L;
    int cpt = 0;
    while (tmp && cpt < i) {//si la liste est vide ou cpt ==i
        tmp = tmp->next;
        cpt++;
    }
    if (cpt == i) {
        return tmp;
    } else {
        return NULL; // indice hors limite
    }
}



Cell* searchList(List* L, char* str){
    Cell *tmp=*L;
    while(tmp){
        if(strcmp(tmp->data,str)==0)
            return tmp;
        tmp=tmp->next;
    }
    return NULL;
}


List* stol(char* s){
    List* li=initList();
    if (strlen(s)==0){//la chaine de char est vide on renvoie une Liste vide
        return li;
    }
    char* tab=strtok(s, "|");
    while (tab){
        Cell* c = buildCell(tab);
        insertFirst(li, c);
        tab = strtok(NULL, "|");
    }
    return li;

}

void ltof(List* L, char* path){
    FILE *f=fopen(path,"w");
    assert(f != NULL && "Erreur :  d'ouverture de fichier");
    char *chaine=ltos(L);//on transforme la liste en une chaine de char        
    int i = 0;
    while (chaine[i] != '\0') {//on ecrit dans le fichier tant que on est pas arrive a la fin de la ligne 
        if (chaine[i] == '|') {//on remplace | par un \n
            fprintf(f, "\n");
        } else {
            fprintf(f, "%c", chaine[i]);
        }
        i++;
    }
    free(chaine);
    fclose(f);
}




List *ftol(char *path) {
    FILE *f = fopen(path, "r");
    assert(f != NULL && "Erreur d'ouverture de fichier");

    char *buffer = malloc(4 * sizeof(char));
    assert(buffer != NULL && "Erreur d'allocation mémoire");

    //lit caractere par caractere
    int c;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        if (i == 4) {
            char *new_buffer = realloc(buffer, 2 * i * sizeof(char));
            assert(new_buffer != NULL && "Erreur de réallocation de mémoire");
            buffer = new_buffer;
        }
    //subsitution du '\n' par '|' 
        if (c == '\n') {
            buffer[i] = '|';
        } else {
            buffer[i] = c;
        }
        i++;
    }
    // ajout du char '/0' fin de chaine
    buffer[i] = '\0';

    fclose(f);

    List *L = stol(buffer);

    free(buffer);

    return L;
}


