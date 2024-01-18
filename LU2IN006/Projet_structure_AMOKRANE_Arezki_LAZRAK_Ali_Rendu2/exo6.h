#ifndef _EXO_6_
#define _EXO_6_

#include "exo3.h"
#include "exo5.h"

typedef struct hashcell{
    Key* key;
    int val;
} HashCell;

typedef struct hashtable{
    HashCell** tab;
    int size;
} HashTable;


CellProtected* tcheck_declaration(CellProtected *list);
HashCell* create_hashcell(Key* key);
int hash_function(Key* key, int size);
int find_position(HashTable* t,Key* key);
HashTable* create_hashtable(CellKey* keys, int size);
void delete_hashtable(HashTable* t);
int occ_key(Key *key,CellKey *list);
Key *compute_winner(CellProtected *decl,CellKey *candidates,CellKey *voters,int sizeC,int sizeV);


#endif