//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "exo2.h"
#include "exo3.h"
#include "exo5.h"
#include "exo6.h"
#include "exo1.h"


CellProtected* tcheck_declaration(CellProtected *list){
    while(list){
        CellProtected* l=list;
        CellProtected* m=list->next;
        if(!verify(list->data)){
            delete_cell_protected(l);
        }
        list=m;
    }
    return list;
}


//creation d'une cellule de table de hachage , stocke une clé et une valeur entière
HashCell *create_hashcell(Key* k){
    HashCell* cellule= (HashCell*) malloc (sizeof(HashCell));
    cellule->key=k;
    cellule->val=0;
    return cellule;
}

//fonction de hachage d'une clé 
int hash_function(Key *k,int taille){
    return (k->val+k->n)%taille;
}


int find_position(HashTable * t, Key * key){
  int size = t->size;
  int pos = hash_function(key, size);

  //Si la case ne corsepond pas a la bonne clé
  if (t->tab[pos] != NULL && t->tab[pos]->key != NULL && key != NULL && ((t->tab[pos]->key->val != key->val) || (t->tab[pos]->key->n != key->n))) {

    int depart = pos;
    pos = (pos + 1) % size;

    //Parcours de la table jusqu'à trouver la bonne clé
    while (pos != depart) {
            if (t->tab[pos] != NULL &&  t->tab[pos]->key != NULL && key != NULL && (t->tab[pos]->key->val == key->val) && (t->tab[pos]->key->n == key->n)) {
                break;
            }
      pos = (pos + 1) % size;
    }

    //la clé n'a pas étais trouve
    if (pos == depart) {
      pos = (pos + 1) % size;

      //Parcours la table jusqu'à trouver une case vide
      while (t->tab[pos] != NULL && pos != depart) {
        pos = (pos + 1) % size;
      }

      //S'il n'y plus de place dans la table de hachage
      if (pos == depart) {
        return -1;
      }
    }
  }
  return pos;
}



HashTable *create_hashtable(CellKey *keys,int size){
    HashTable *table=(HashTable *)malloc(sizeof(HashTable));
    if (table==NULL){
        printf("ERREUR D'ALLOCATION MEMOIRE\n");
        exit(-1);
    }
    table->size=size;
    table->tab=(HashCell **)malloc(sizeof(HashCell *)*size);
    if (table->tab==NULL){
        printf("ERREUR D'ALLOCATION MEMOIRE\n");
        exit(-1);
    }
    for(int i=0;i<size;i++){ // Initialisation des éléments à NULL (étant donné que ce n'est pas le cas automatiquement)
        table->tab[i]=NULL;
    }
    while (keys!=NULL){
        int hash=hash_function(keys->data,size);
        if (table->tab[hash]!=NULL){
            for(int i=0;i<size;i++){
                if(table->tab[(hash+i)%size]==NULL){
                    table->tab[(hash+i)%size]=create_hashcell(keys->data);
                    break;
                }
            }
        } else {
            table->tab[hash]=create_hashcell(keys->data);
        }
        keys=keys->next;
    }

    return table;
}


//Fonction de suppression d'une table de hachage en mémoire
// Aucune suppression de clé n'est faite, faites appel à delete_list_keys pour cela*/
void delete_hashtable(HashTable *t){
    for(int i=0;i<t->size;i++){
        if (t->tab[i]!=NULL){
            free(t->tab[i]);
        }
    }
    free(t->tab);
    free(t);
}


//fonction pour simplifé compute_win
//vérifie l'occurence de la clé dans la liste"
//Renvoie 1 si occurence il y a,0 sinon"
int occ_key(Key *key,CellKey *list){
    while (list!=NULL){
        if (key->val==list->data->val && key->n==list->data->n){
            return 1;
        }
        list=list->next;
    }
    return 0;
}



/*
la fonction retourne le gagnant des élections
"Renvoie la clé avec le plus d'occurence"
"Vérifie la presence de la clés (dans les déclarations) dans la liste candidates"
"Vérifie la presence de la clé publique(dans la décleration) dans la liste voters"
*/

Key *compute_winner(CellProtected *decl,CellKey *candidates,CellKey *voters,int sizeC,int sizeV){
    if (voters==NULL || candidates==NULL || decl==NULL){
        return NULL;
    }
    HashTable *tableC=create_hashtable(candidates,sizeC);
    HashTable *tableV=create_hashtable(voters,sizeV);
    CellProtected *declarations=decl;
    while(declarations!=NULL){
        
        if (occ_key(declarations->data->pKey,voters)){
            
            if (tableV->tab[find_position(tableV,declarations->data->pKey)]->val==0){ // Est-ce que l'électeur n'a pas voté ?
                tableV->tab[find_position(tableV,declarations->data->pKey)]->val=1;
                Key *ck=str_to_key(declarations->data->mess);
                if (occ_key(ck,candidates)){ // Est-ce que le candidat est légitime ?
                    tableC->tab[find_position(tableC,ck)]->val++;
                }
                free(ck);
            }
        }
        declarations=declarations->next;
    }

    HashCell *max=NULL;
    for(int i=0;i<sizeC;i++){ // Recherche du premier élément HashCell non nul pour initialiser le max
        if (tableC->tab[i]!=NULL){
            max=tableC->tab[i];
            break;
        }
    }
    for(int i=1;i<sizeC;i++){ // Comparaison des nombres d'occurences pour déterminer le max
        if (tableC->tab[i]!=NULL && tableC->tab[i]->val > max->val){
            max=tableC->tab[i];
        }
    }
    Key *res=(Key *)malloc(sizeof(Key));
    if (res==NULL){
        printf("ERREUR D'ALLOCATION MEMOIRE\n");
        exit(-1);
    }
    init_key(res,max->key->val,max->key->n);
    delete_hashtable(tableC);
    delete_hashtable(tableV);
    return res;
}





