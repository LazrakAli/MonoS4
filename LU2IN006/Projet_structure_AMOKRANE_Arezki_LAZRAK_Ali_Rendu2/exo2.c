//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "exo1.h"
long extended_gcd(long s, long t, long *u, long *v){
    if(s==0){
        *u=0;
        *v=1;
        return t;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
    *u=vPrim-((t/s)*uPrim);
    *v=uPrim;
    return gcd;
}
//genere des couple de clés Publique/privé
void generate_key_values(long p,long q,long *n,long *s,long *u){
    long v;
    long t=(p-1)*(q-1);
    *n=p*q;
    *s=rand_long(0,t);
    while (extended_gcd(*s,t,u,&v)!=1 || (*s**u)%t!=1){
        *s=rand_long(0,t);
    }
}
//la fonction chiffre la chaine de caractères chaine avec la clé publique pkey
long* encrypt(char* chaine, long s, long n){
    long *crypt=(long*)malloc(strlen(chaine)*sizeof(long));
     if (crypt==NULL){
        printf("Erreur d'allocation memoire \n");
        exit(-1);
     }
    int i=0;
    int d;
    while(chaine[i]!='\0'){  // parcourir la chaine 
        d=chaine[i];
        crypt[i]=modpow(d, s, n);
        i++;
    }
    return crypt; // retourne un tableau de long obtenant en chiffrant ces entiers.
}
//la fonction déchiffre un message à l'aide de la clé secrète skey 
char* decrypt(long* crypt, int size, long u, long n){
    if (crypt==NULL) {
        return NULL;
    }
    //Une allocation memoire
    char* decrypt=malloc(size*sizeof(char)+1);
    // verification de l'allocation memoire
     if (decrypt==NULL){
        printf("Erreur d'allocation  memoire \n");
        exit(-1);
     }
    int i;
    for(i=0;i<size;i++){
        decrypt[i]=(char)modpow(crypt[i],u,n);
    }
    decrypt[size]='\0'; // le caractère spécial \0 à la fin.
    return decrypt; // renvoie une chaine de caractère obtenue 

}
