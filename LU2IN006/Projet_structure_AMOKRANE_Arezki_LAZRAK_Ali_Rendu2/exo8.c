//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include "exo3.h"
#include "exo1.h"
#include "exo2.h"
#include "exo5.h"
#include "exo7.h"
#include "exo8.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <openssl/sha.h>


/*sauvegarde un bloc dans un fichier <filename>*/
void keep_block(Block *b,char *filename){
    FILE *f=fopen(filename,"w");
    CellProtected *cp=b->votes;
    char *kstr=key_to_str(b->author);
    char *pstr=NULL;

    fprintf(f,"%s %s %s %d\n",kstr,b->previous_hash,b->hash,b->nonce);
    free(kstr);

    while (cp!=NULL){
        pstr=protected_to_str(cp->data);
        fprintf(f,"%s\n",pstr);
        free(pstr);
        cp=cp->next;
    }
    fclose(f);
}



/*Fonction de création d'un noeud*/
CellTree *create_node(Block *b){
    CellTree *cell=(CellTree *)malloc(sizeof(CellTree));
    if (cell==NULL){
        printf("ERREUR MALLOC\n");
        exit(-1);
    }
    cell->block=b;
    cell->father=NULL;
    cell->firstChild=NULL;
    cell->nextBro=NULL;
    cell->height=0;

    return cell;
}

/*Fonction de mise à jour de la hauteur du noeud father*/
int update_height(CellTree *father,CellTree *child){
    int maximum=fmax(father->height,child->height+1);
    if (maximum==father->height){
        return 0;
    }
    father->height=maximum;
    return 1;
}

/*Fonction d'ajout en tête d'un noeud fils child au noeud père father*/
void add_child(CellTree *father,CellTree *child){
    if (father==NULL){
        father=child;
        return;
    }
    // Ajout en tête du fils
    child->nextBro=father->firstChild;
    father->firstChild=child;

    // Modification de la hauteur des parents
    CellTree *ftmp=father;
    CellTree *ctmp=father->firstChild;
    while (ftmp!=NULL){
        update_height(ftmp,ctmp);
        ftmp=ftmp->father;
        ctmp=ctmp->father;
    }
}

/* Fonction d'affichage d'un arbre
--  ATTENTION : PROF DOIT ETRE APPELE AVEC LA VALEUR 0*/
void print_tree(CellTree *racine,int prof){
    if (racine==NULL){
        return;
    }
    char tabs[racine->height];
    CellTree *cour=racine;
    memset(tabs,'\t',prof);
    tabs[prof]='\0';
    while (cour!=NULL){
        printf("%sHauteur:%d Hash:%s\n",tabs,cour->height,cour->block->hash);
        print_tree(cour->firstChild,prof+1);
        cour=cour->nextBro;
    }
}

/*supprime d'un noeud*/
void delete_node(CellTree *node){
    if (node==NULL){
        return;
    }
    if (node->block!=NULL){
        delete_block(node->block);
    }
    free(node);
}

/*supprime d'un arbre*/
void erase_tree(CellTree *tree){
    if (tree==NULL){
        return;
    }
    CellTree *child=tree->firstChild;
    CellTree *tmp;
    while (child!=NULL){
        tmp=child->nextBro;
        erase_tree(child);
        delete_node(child);
        child=tmp;
    }
}

/*recherche la hauteur la plus élevée d'un enfant*/
CellTree *highest_child(CellTree *cell){
    if (cell->firstChild==NULL){
        return NULL;
    }
    CellTree *child=cell->firstChild->nextBro;
    CellTree *max=cell->firstChild;
    while (child !=NULL){
        if (max->height<child->height){
            max=child;
        }
        child=child->nextBro;
    }
    return max;
}

/*Fonction de recherche du noeud ayant le parcours le plus long*/
CellTree *last_node(CellTree *tree){
    if (tree->firstChild==NULL){
        return tree;
    }
    return last_node(highest_child(tree));
}


CellProtected *fusion_highest_CP(CellTree *racine){
    CellProtected *res=racine->block->votes;
    CellProtected *tmp=racine->block->votes;
    while ((tmp!=NULL) && (tmp->next!=NULL)){
        tmp=tmp->next;
    }
    CellTree *cour=highest_child(racine);


    while (cour!=NULL){
        fusion_cell_protected(&tmp,cour->block->votes);
        cour=highest_child(racine);
        while ((tmp!=NULL) && (tmp->next!=NULL)){
            tmp=tmp->next;
        }
    }
    return res;
}

