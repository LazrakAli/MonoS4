//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include "exo5.h"
#include "exo7.h"
#include "exo8.h"
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <openssl/sha.h>


//Fonction permettant d'écrire dans un fichier un bloc
void write_block(char *nomfic, Block* block){
    FILE *f = fopen(nomfic, "w"); // ouverture du fichier
    if(f == NULL){
        printf("Erreur d'ouverture du fichier %s\n", nomfic);
        return;
    }
    char *keystr = key_to_str(block->author); 
    fprintf(f, "%s\n", keystr);
    for(int i=0 ; i<SHA256_DIGEST_LENGTH ; i++){
        fprintf(f, "%02x", block->hash[i]);
    }
    fprintf(f, "\n");
    for(int i=0 ; i<SHA256_DIGEST_LENGTH ; i++){
        fprintf(f, "%02x", block->previous_hash[i]);
    }
    fprintf(f, "\n%d\n", block->nonce);
    CellProtected *cell = block->votes;
    while(cell){
        char *votestr = protected_to_str(cell->data);
        fprintf(f, "%s\n", votestr);
        cell = cell->next;
        free(votestr);
    }
    free(keystr);
    fclose(f); // fermeture du fichier
}




//Fonction permettant la lecture d'un bloc dans un fichier
Block *read_block(char *filename){
    FILE *f=fopen(filename,"r"); // ouverture du fichier
    if (f==NULL){
        printf("ERREUR  à l'ouverture du fichier \n");
        exit(-1);
    }
    Block *bk=(Block *)malloc(sizeof(Block)); // allocation d'un bloc 
    bk->hash=(unsigned char *)malloc(sizeof(unsigned char)*256);
    bk->previous_hash=(unsigned char *)malloc(sizeof(unsigned char)*256);
    if (bk==NULL){
        printf("Erreur d'allocation mémoire\n");
        exit(-1);
    }
    char kstr[256];
    char pstr[512];
    bk->votes=NULL;
    char buffer[512];
    fgets(buffer,512,f);// get une ligne dans le fichier f 
    sscanf(buffer,"%s %s %s %d",kstr,bk->previous_hash,bk->hash,&(bk->nonce));
    bk->author=str_to_key(kstr);
    // On a besoin d'éviter l'inversion des ajouts en tête
    // Donc on n'utilise pas add_head_cellprotected
    if (fgets(buffer,512,f)!=NULL){ // Premier élément 
        sscanf(buffer,"%s\n",pstr);
        bk->votes=create_cell_protected(str_to_protected(buffer));
        CellProtected *lastelement=bk->votes;
        while (fgets(buffer,512,f)!=NULL){ // Elements suivants
            sscanf(buffer,"%s\n",pstr);
            lastelement->next=create_cell_protected(str_to_protected(buffer));
            lastelement=lastelement->next;
        }
    }
    fclose(f); // fermeture du fichier 
    return bk;
}




//Fonction génère une chaine de caractère représentant un bloc
char *block_to_str(Block *block){
    char *str=(char *)malloc(sizeof(char)*1024);
    char *c=(char *)malloc(sizeof(char)*256);
    if (str==NULL || c==NULL){
        printf("Erreur d'allocation\n");
        exit(-1);
    }
    char *ky=key_to_str(block->author);
    c[0]='\0';
    char *cpstrtmp;
    CellProtected *q=block->votes;
    while (q!=NULL){
        cpstrtmp=protected_to_str(q->data);
        strcat(cpstrtmp,"\n");
        c=(char *)realloc(c,strlen(c)+128*sizeof(char));
        strcat(c,cpstrtmp);
        free(cpstrtmp);
        q=q->next;
    }
    str=realloc(str,strlen(c)+256*sizeof(char));
    sprintf(str,"%s %s\n%s",ky,block->previous_hash,c);
    free(ky);
    free(c);
    return str;
}



/*Fonction de hachage avec protocole SHA256
-- Retour : Chaîne de caractères et non valeurs hexadécimales*/
unsigned char *hash_char( char *str){
    unsigned char *r=(unsigned char *)malloc(sizeof(char)*256);
    if (r==NULL){
        printf("Erreur d'allocation \n");
        exit(-1);
    }
    unsigned char *d=SHA256((unsigned char *)str,strlen(str),0);
    // J'évite les boucles for ici pour ne avoir à appeler qu'une seule fois sprintf au lieu d'appeler 32 fois sprintf et strcat
    sprintf((char *)r,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8],d[9],d[10],d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19],d[20],d[21],d[22],d[23],d[24],d[25],d[26],d[27],d[28],d[29],d[30],d[31]);
    return r;
}

void compute_proof_of_work(Block *b,int d){
    unsigned char *hash;
    char zeros[d+1];
    memset(zeros,'0',d);
    zeros[d]='\0';
    char *bk=block_to_str(b);
    char tohash[strlen(bk)+sizeof(int)+2];
    char *hashcomp;
    for(int i=0;i<INT32_MAX;i++){
        b->nonce=i;
        sprintf(tohash,"%s%d",bk,i);
        hash=hash_char(tohash);
        hashcomp=strdup((char *)hash);
        hashcomp[d]='\0'; // caractère spécial 
        if (strcmp((const char *)hashcomp,zeros)==0){
            printf("%s %d - OKEY -!\n",hash,i);
            b->hash=hash;
            b->nonce=i;
            free(bk);
            free(hashcomp);
            return;
        }
        free(hashcomp);
        free(hash);
    }
    b->nonce=-1;
    printf("non trouvé\n");
}



//Fonction qui vérifie qu'un block est valide
int verify_block(Block* B, int d){
    int i=0;
    while (i<d){
        if (B->hash[i]!='0'){
            return 0;
        }
        i++;
    }
    return 1;
}



//Fonction qui supprime un bloc 
void delete_block(Block* b){
    free(b->hash);
    free(b->previous_hash);
    CellProtected *p;
    while(b->votes){
        p = b->votes->next;
        free(b->votes);
        b->votes = p;
    }
    free(b);
}


