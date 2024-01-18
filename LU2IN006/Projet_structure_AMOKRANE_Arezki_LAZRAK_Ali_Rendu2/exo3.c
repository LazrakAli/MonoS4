//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "exo3.h"

//initialise une cle deja instancié
void init_key(Key* key, long val, long n){
	key->val = val;
	key -> n = n;
}
// la fonction utilise le protocole RSA pour initialiser une clé publique et une clé sectère
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
	long p = random_prime_number (low_size ,up_size, 5000); // générer un nombre premier 
 	long q = random_prime_number (low_size ,up_size , 5000); // généerer un nombre premier
 	while ( p == q ){
 		q = random_prime_number (low_size,up_size , 5000); // généerer un nombre premier
 	}
 	long n=0, s=0, u=0;
 	while (s==u){
	generate_key_values(p ,q ,&n,&s,&u); // génerer une pkey et skey
	}
 	init_key(pKey, s, n); // initialisation de la clé publique 
 	init_key(sKey, u, n); // initialisation de la clé secète 
 	
 	//printf ( " cle publique = (%lx , %lx ) \n" ,s , n ) ;
 	//printf ( " cle privee = (%lx , %lx ) \n" ,u , n ) ;
 }
 //la fonction permet de passer d'une variable Key à sa représnetation sous forme de chaine de caractères
char* key_to_str(Key* key){
	char * str = malloc(sizeof(char)* 100);
	assert(str); //si y'a une erreur d'allocation
	sprintf(str, "(%lx,%lx)", (key->val), (key->n));
 	
 	return str;
}
 //la fonction permet de passer d'une variable chaine de caractères à sa représnetation sous forme de key
Key* str_to_key(char* str){
	Key * ky = malloc(sizeof(Key));
	assert(ky); //si y'a une erreur d'allocation
	sscanf(str,"(%lx,%lx)",&(ky->val),&(ky->n));
    return ky;
}


//Fonction de libération d'une signature
void free_signature(Signature *sgn){
    if (sgn==NULL){
        return;
    }
    if (sgn->tab!=NULL){
        free(sgn->tab);
    }
    free(sgn);

}
// initialisation d'une signature
 Signature* init_signature(long* content, int size){
 	Signature * s = malloc(sizeof(Signature));
 	assert(s); //si y'a une erreur d'allocation
 	long* tab = malloc(sizeof(long)*size); // allocation d'un tableau  de taille size 	
 	for(int i=0; i<size; i++){
 		tab[i]=content[i];
 		//printf("tab[%d]=%lx \n", i, tab[i]);
 	}
 	s->tab = tab; 
 	s->n = size;
 	
 	return s;
 }   
 //la fonction crée une signature à partir du message mess  et de skey
 Signature* sign(char* mess, Key* sKey){
 	long * tab = encrypt(mess, sKey->val, sKey->n);
 	
 	Signature * s = init_signature(tab, strlen(mess));
 	
 	return s;
 }

//la fonction permet de passer d'une variable signature à sa représnetation sous forme de chaine de caractères
char * signature_to_str ( Signature * sgn ) {
	char * result = malloc (10* sgn->n * sizeof ( char ) ) ;
	result[0]='#';
	int pos = 1;
	char buffer[156]; // buffer
	for ( int i =0; i < sgn->n ; i ++) {
		sprintf( buffer , "%lx" , sgn->tab[i]) ;
		for (int j=0; j<strlen(buffer); j++) {
			result[pos] = buffer[j];
 			pos = pos +1;
 		}
		result[pos] = '#' ;
 		pos = pos +1;
 	}
 	result[pos] = '\0' ;
 	result = realloc (result , ( pos +1) * sizeof ( char ) ) ;
 	return result;
 }
//la fonction permet de passer d'une variable chaine de caractère à sa représnetation sous forme de signature
 Signature * str_to_signature ( char * str ) {
 	int len = strlen ( str ) ;
 	long * content = ( long *) malloc ( sizeof ( long ) * len ) ;
 	int num = 0;
 	char buffer [256];

    int pos = 0;
	for ( int i =0; i < len ; i++) {
		if ( str[i] != '#' ) {
			buffer[pos] = str[i];
			pos = pos +1;
		} else {
			if ( pos != 0) {
				buffer[pos] = '\0' ;
				sscanf( buffer , "%lx", &(content[num]) ) ;
				num = num + 1;
				pos = 0;
			}
		}
	}
	content = realloc ( content , num * sizeof ( long ) ) ;
	return init_signature ( content , num ) ;
}	
 	
 //initialisation de la structure Protected	
Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
	Protected* pr = malloc(sizeof(Protected));
	assert(pr); // si y'a erreur d'allocation
	pr->pKey = pKey;
	pr->mess = strdup(mess);
	pr->sgn = sgn;              
	
	return pr; 
}

//la fonction vérifie que la signature contenue dans pr correspond bien au message et à la personne contenus dans pr 
int verify(Protected *pr){
    char *tb=decrypt(pr->sgn->tab,pr->sgn->n,pr->pKey->val,pr->pKey->n);
    char dcry[500];
    strcpy(dcry,tb);
    free(tb);
    return strcmp(pr->mess,dcry);
}
//la fonction permet de passer d'une variable de type Protected à sa représnetation sous forme de chaine de caractères
char* protected_to_str(Protected* pr){
	char * str = malloc(sizeof(char)* 100);
	
	sprintf(str, "%s %s %s", key_to_str(pr->pKey), strdup(pr->mess), signature_to_str(pr->sgn));
 	
 	return str;
}
	
//la fonction permet de passer d'une variable  chaine de caractère à sa représnetation sous forme de type Protected
Protected* str_to_protected(char* str){
	Protected* pr = malloc(sizeof(Protected));
	assert(pr);
	char key[50], mess[50], signature[50];
	
	sscanf(str, "%s %s %s", key, mess, signature);
	
	pr->pKey = str_to_key(key);
	pr->mess = strdup(mess);
	pr->sgn = str_to_signature(signature);
	
	return pr;
}
//la fonction recherche si la valeur val est dans le tableau tab de taille size 
 int occurence_int(int val, int *tab,int size){
	 for (int i=0;i<size;i++){
		 if (val==tab[i]){
			 return 1 ;
		 }
	 }
	 return 0;
 }

//EXO4
//Fonction de création de données d'élections
//Les données sont stockés dans les fichiers keys.txt,candidates.txt et declarations.txt*/
void generate_random_data(int nv,int nc){
    // ouverture des fichiers
	FILE *keys=fopen("keys.txt","w");
    FILE *candidates=fopen("candidates.txt","w");
    FILE *declarations=fopen("declarations.txt","w");
    Key *pktab[nv];
    Key *sktab[nv];
    Key *cptab[nc];
    int nonocc[nc];
    char *mess;
    char *str;
    char *str2;
    int rd;
    Signature *sgn;
    // Ecriture du fichier keys.txt
    for(int i=0;i<nv;i++){
        pktab[i]=(Key *)malloc(sizeof(Key)); // allocation du pkey
        sktab[i]=(Key *)malloc(sizeof(Key)); // allocation du skey
        init_pair_keys(pktab[i],sktab[i],3,7); // générer pkey et skey
        str=key_to_str(sktab[i]); //transformer skey to str  
        str2=key_to_str(pktab[i]);// transformer pkey to str 
        fprintf(keys,"%s %s\n",str2,str); //ecriture dans le fichier
        free(str);
        free(str2);
    }
    // Ecriture du fichier candidates.txt
    for(int i=0;i<nc;i++){
        srand(time(NULL)*rand());
        rd=rand()%nv;
        while(occurence_int(rd,nonocc,i+1)){ // pour ne pas génerer deux candidats identique 
            rd=rand()%nv;
        }
        cptab[i]=pktab[rd];
        nonocc[i]=rd; 
        str=key_to_str(cptab[i]);
        fprintf(candidates,"%s\n",str); //ecriture dans le fichier
        free(str);
    }




    // Ecriture du fichier declarations.txt
    for(int i=0;i<nv;i++){
        srand(time(NULL)*rand());
        int rdm=rand()%nc;
        char *pkstr=key_to_str(pktab[i]);
        mess=key_to_str(cptab[rdm]); 
        sgn=sign(mess,sktab[i]); 
        str=signature_to_str(sgn);
        fprintf(declarations,"%s %s %s\n",pkstr,mess,str); //ecriture dans le fichier
        //libération des variables 
		free(str);
        free(mess);
        free(pkstr);
        free_signature(sgn);
    }
    // Libération des clés
    for(int i=0;i<nv;i++){
        free(sktab[i]);
        free(pktab[i]);
    }
	//cloture des fichiers
    fclose(keys);
    fclose(candidates);
    fclose(declarations);
}









