#ifndef EXO9_H
#define EXO9_H

#include "exo8.h"

void create_block(CellTree **tree,Key *author,int d);
void add_block(int d,char *name);
void submit_vote(Protected *p);
Key *compute_winner_BT(CellTree *tree,CellKey *candidates,CellKey *voters,int sizeC,int sizeV);
CellTree *read_tree();
#endif