#ifndef _EXO_8_
#define _EXO_8_

#include "exo3.h"
#include "exo5.h"
#include "exo7.h"

typedef struct block_tree_cell{
    Block *block;
    struct block_tree_cell *father;
    struct block_tree_cell *firstChild;
    struct block_tree_cell *nextBro;
    int height;
}CellTree;



void keep_block(Block *b,char *filename);
CellTree *create_node(Block *b);
int update_height(CellTree *father,CellTree *child);
void add_child(CellTree *father,CellTree *child);
void print_tree(CellTree *racine,int prof);
void delete_node(CellTree *node);
void erase_tree(CellTree *tree);
CellTree *highest_child(CellTree *cell);
CellTree *last_node(CellTree *tree);
CellProtected *fusion_highest_CP(CellTree *racine);



#endif