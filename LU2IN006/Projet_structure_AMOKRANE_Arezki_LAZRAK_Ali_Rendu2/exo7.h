#ifndef _EXO_7
#define _EXO_7
#include "exo3.h"
#include "exo5.h"

typedef struct block{
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
}Block;



void write_block(char *nomfic, Block* block);
Block* read_block(char* nomfic);
char* block_to_str(Block* block);
unsigned char* hash_char(char* str);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block* B, int d);
void delete_block(Block* b);


#endif

