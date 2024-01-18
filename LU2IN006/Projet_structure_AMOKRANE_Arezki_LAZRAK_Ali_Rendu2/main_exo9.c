#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include "exo1.h"
#include <math.h>
#include "exo2.h"
#include "exo3.h"
#include "exo5.h"
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include "exo6.h"
#include "exo7.h"
#include "exo8.h"
#include "exo9.h"


#define E 4

void liberation_de_la_memoire(CellTree *tree){
    if (tree!=NULL){
        liberation_de_la_memoire(tree->firstChild);
        liberation_de_la_memoire(tree->nextBro);
        free(tree->block->author);
        free(tree->block->hash);
        free(tree->block->previous_hash);
        free(tree->block);
        free(tree);
    }
}



int main(){
    generate_random_data(1000,5);
    
    CellKey *candidates=read_public_keys("candidates.txt");
    CellKey *keys=read_public_keys("keys.txt");
    CellProtected *votes=read_protected("declarations.txt");

    CellProtected *tempo=votes;
    CellTree *tree=NULL;
    int c=1;
    int fc=0;
    char filename[256];
    while (tempo!=NULL){
        submit_vote(tempo->data);
        if (c%10==0){
            sprintf(filename,"Blockchain/B%d.txt",fc);
            create_block(&tree,tempo->data->pKey,E);
            add_block(E,filename);

            fc++;
        }
        c++;
        tempo=tempo->next;
    }
    CellTree *rtree=read_tree();
    print_tree(rtree,0);

    Key *k=compute_winner_BT(rtree,candidates,keys,3,500);
    char *kstr=key_to_str(k);
    printf("Vainqueur : %s\n",kstr);

    free(k);
    free(kstr);

    erase_tree(tree);
    liberation_de_la_memoire(rtree);
    delete_list_keys(keys);
    delete_list_keys(candidates);
    delete_list_protected(votes);


    
    

    return 0;
}