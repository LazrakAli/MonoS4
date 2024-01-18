#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include "exo7.h"
#include "exo8.h"
#include <math.h>
#include "exo2.h"
#include "exo1.h"
#include "exo5.h"
#include <time.h>
#include <stdlib.h>
#include "exo6.h"



int main(){
    int z=3;
    FILE *f=fopen("data.txt","a");
    for(int i=0;i<10;i++){
        generate_random_data(10,3);
        Block *b=(Block *)malloc(sizeof(Block));
        Key *k=(Key *)malloc(sizeof(Key));
        CellProtected *d=valid_list_protected(read_protected("declarations.txt"));
        init_key(k,551,58);
        
        b->votes=d;
        b->previous_hash=NULL;
        b->author=k;
        clock_t begin=clock();
        
        compute_proof_of_work(b,z);
        
        clock_t end=clock();
        fprintf(f,"%d %f\n",z,(double)(end -  begin)/ CLOCKS_PER_SEC);
    }
    fclose(f);
    return 0;
};
