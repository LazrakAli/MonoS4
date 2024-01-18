//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include "exo3.h"
#include "exo1.h"
#include "exo2.h"
#include "exo5.h"
#include "exo6.h"
#include "exo7.h"
#include "exo8.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <dirent.h> 
#include <openssl/sha.h>




/*création d'un bloc a partir d'un fichier*/
void create_block(CellTree **tree,Key *author,int d){
    Block *bk=(Block *)malloc(sizeof(Block));

    if (bk==NULL){
        printf("Erreur d'allocation\n");
        exit(-1);
    }

    CellProtected *plist=read_protected("Blockchain/Pending_votes.txt"); 
    CellTree *lastnode=last_node(*tree);
    
    bk->author=author;
    bk->votes=plist;
    if (lastnode==NULL){
        bk->previous_hash=NULL;
        *tree=create_node(bk);
    } else {
        bk->previous_hash=(unsigned char *)strdup((char *)lastnode->block->hash);
    }
    
    compute_proof_of_work(bk,d);
    CellTree *cell=create_node(bk);
    add_child(lastnode,cell);
    keep_block(bk,"Blockchain/Pending_block");
    remove("Blockchain/Pending_votes.txt");
}


/*ajoute un bloc dans le dossier Blockchain*/
void add_block(int d,char *name){
    Block *bk=read_block("Blockchain/Pending_block");
    if (verify_block(bk,d)==1){
        keep_block(bk,name);
    }

    delete_list_protected(bk->votes);
    bk->votes=NULL;
    free(bk->author);
    delete_block(bk);
    remove("Blockchain/Pending_block");
}

/*Depot d'un vote, il sera ajouté à la fin du fichier Pending_votes.txt*/
void submit_vote(Protected *p){
    FILE *f=fopen("Blockchain/Pending_votes.txt","a");
    if (f==NULL){
        printf("Erreur d'écriture dans le fichier \n");
        exit(-1);
    }
    char *str=protected_to_str(p);
    fprintf(f,"%s\n",str);
    free(str);
    fclose(f); // fermeture du fichier 
}



CellTree *read_tree(){
    // Recherche du nombre de fichiers dans le dossier Blockchain
    // Possible de faire un seul parcours du dossier et avoir un tableau à taille variable (realloc)
    int c=0;
    DIR *repc=opendir("./Blockchain/");
    if (repc !=NULL){
        struct dirent *dir;
        while ((dir=readdir(repc))){
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                c++;
            }
        }
        closedir(repc);
    }

    // Création des blocs
    CellTree *tab[c];
    CellTree *racine=NULL;
    int maxi=0;
    DIR *rep=opendir("./Blockchain/");
    char filename[1080]; // Implique une taille maximale de nom de fichier
    if (rep!=NULL){
        struct dirent *dir;
        while ((dir=readdir(rep))){
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                sprintf(filename,"Blockchain/%s",dir->d_name);
                tab[maxi]=create_node(read_block(filename));
                maxi++;
            }
        }
        closedir(rep);
    }
    // Recherche des liens père/fils
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxi;j++){
            if (j==i){
                continue;
            }
            if (strcmp((char *)tab[j]->block->previous_hash,(char *)tab[i]->block->hash)==0){
                add_child(tab[i],tab[j]);
            }
        }
    }
    // Recherche de la racine
    for(int k=0;k<maxi;k++){
        if (tab[k]->father==NULL){
            racine=tab[k];
        }
    }
    return racine;
} 

Key *compute_winner_BT(CellTree *tree,CellKey *candidates,CellKey *voters,int sizeC,int sizeV){
    CellTree *q=tree;
    CellProtected *list=NULL;
    while (q!=NULL){      
        fusion_cell_protected(&list,q->block->votes);
        q=highest_child(q);
    }
    CellProtected *vlist=valid_list_protected(list);
    return compute_winner(vlist,candidates,voters,sizeC,sizeV);
}



