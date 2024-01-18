#ifndef EXO_5
#define EXO_5

#include "exo3.h"



typedef struct cellKey{
    Key *data;
    struct cellKey *next;
}CellKey;

typedef struct cellProtected{
    Protected *data;
    struct cellProtected *next;
}CellProtected;



CellKey *create_cell_key(Key *key);
CellKey *en_tete_cellkey(CellKey *list,Key *key);
CellProtected *create_cell_protected(Protected *pr);
CellProtected *en_tete_cellprotected(CellProtected *list,Protected *cpr);
CellKey *read_public_keys(char *fichier);
void delete_cell_key(CellKey *c);
void delete_list_keys(CellKey *list);
void print_list_protected(CellProtected *LCP);
CellProtected *read_protected();
void print_list_keys(CellKey *LCK);
void fusion_cell_protected(CellProtected **first, CellProtected *second);
void delete_cell_protected(CellProtected *c);
void delete_list_protected(CellProtected *list);
CellProtected *valid_list_protected(CellProtected *list);

char *CPlist_to_str(CellProtected *list);

#endif