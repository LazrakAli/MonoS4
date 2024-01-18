Arezki AMOKRANE 28610421
Ali LAZRAK
Projet structure de données 

exo1 : Réolution du problème de primalité
Q 1.1 :
la fonction is_prime_naive renvoie 1 si P est premier et 0 sinon .
l'implémentation de la fontion:
int is_prime_naive(long n)
{
	for(int i = 2 ; i<n ; i++)  
	{
		if( n%i==0) //Dans ce cas i divise n, ce qui implique que p n'est pas premier 
		{
			return 0; 
		}

	}
	

	return 1;

}

c'est une foncton de complexité O(n) , car dans le pire des cas on passe n itération dans la boucle while.(Possibilité de l'améliorer en oubliant le test sur les nombres pairs)

Q 1.2 :
le plus grand nombre premier qu'on a atteint en 2 millièmes de secondes avec cette fonction est  : 53419

Q 1.3 : 
la fonction modpow_naive retourne la valeur a^b mod n 
l'implémentation de la fonction:
long  modpow_naive(long a , long m , long n)
{
	long res = 1;
	for(int i = 1 ; i<=m ; i++) 
	{
		res =  (res*a) % n  ;	

	}

	return res  ;

}


la complexité de cette algorithme est O(m)

Q 1.4 :
la fonction modpow réalise une succession d'élévation au carré celon une méthode bien défini
l'implémentation de la fonction :

long modpow(long a , long m , long n )
{
	if(m==0)
	{
		return 1;
	}

	long b;
	if(m%2 == 0)
	{
		b = modpow(a , m/2 , n);

		return b*b % n;
	}
	else
	{
		b = modpow(a , m/2 , n);

		return a*b*b % n ;
	}
}

En utilisant la récursivité on obtient une fonction qui vérifie est ce que n est un nombre premier, beaucoup plus performante que is_prime_naive
Q 1.5 :
comparez les performances des deux méthodes en tracant une courbe ? que remarquez vous ?



 on remearque sur le graphe que modpow est plus rapide que modpow_naive
Q 1.7 : 
la Borne supérieur sur la probabilité d'erreur de l'algorithme est : 1/4K si l'algorithme génére K valeurs 

Q 1.8 : 
On utilise la fonction random_long pour générer un long aléatoire entre une certaine
intervalle puis avec le test de miller on vérifie sa primarité en s’assurant que c’est des entiers qui sont au plus de 7 bits , et on a créé notre propre fonction qui nous permet d’élever à une puissance
l'implémentation: 
long rand_long(long low_size , long  up_size)
{
	return rand() % (up_size - low_size  +1  ) + low_size ;
}

La fonction random_prime_number retourne un nombre premier de taille comprise entre low_size et up_size 
L'implémentation de la fonction 

long random_prime_number(int ls,int us,int k){
    long res;
    for(int i=0;i<10000;i++){
		double x=pow(2,ls-1);
		double y=pow(2,us)-1;
        res= rand_long(x,y);
        if (is_prime_miller(res,k)){
            return res;
        }
    }
    return -1;
}
EXO2 :Implémentation du protocole RSA
Q 2.1 : 
La fonction generate_key_values permet de générer la clé publique pkey et la clé secrète skey , à partir des nombres premiers p et q , en suivant le protocole RSA.
l'implémentation de la fonction :
void generate_key_values(long p, long q, long* s, long *n, long *u){
    srand(time(NULL));
    *n = p*q;
    long t = (p-1)*(q-1);
    long v = 1;
    while(extended_gcd(*s,t,u,&v)!=1){
        *s = rand_long(0,t);
    }
}
Q 2.2:
La fonction encrypt qui chaine de caractères chaine avec le clé publique pkey.
l'implémentation de la fonction :
long* encrypt(char* chaine, long s, long n){
    long *crypt=(long*)malloc(strlen(chaine)*sizeof(long));
     if (crypt==NULL){
        printf("Erreur d'allocation \n");
        exit(-1);
     }
    int i=0;
    int d;
    while(chaine[i]!='\0'){
        d=chaine[i];
        crypt[i]=modpow(d, s, n);
        i++;
    }
    return crypt;
}
Q 2.3:
La fonction decrypt qui déchiffre  à l'aide de la clé secrète skey 
l'implémentation de la fonction :
char* decrypt(long* crypt, int size, long u, long n){
    if (crypt==NULL) {
        return NULL;
    }
    //Une allocation memoire pour decrypter
    char* decrypt=malloc(size*sizeof(char)+1);
    // verification de l'allocation memoire
     if (decrypt==NULL){
        printf("Erreur d'allocation \n");
        exit(-1);
     }
    int i;
    for(i=0;i<size;i++){
        decrypt[i]=(char)modpow(crypt[i],u,n);
    }
    decrypt[size]='\0';
    return decrypt;

}
EXO3 : Manipulations de structures sécurisées
Q 3.1:
 définition de la structure Key :
typedef struct Key{
    long val,n;
}Key;

Q 3.2 :
 la fonction init_key inisilise une clé déja allouée
l'implémentation de la fonction :
void init_key(Key* key, long val, long n){
	key->val = val;
	key -> n = n;
}
Q3.3:
 la fonction init_pair_keys inisilise une clé déja allouée , (on génére d'abords  aléatoirement des clé public et privé puis on initialise une clé privé et public)
l'implémentation de la fonction :
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
	long p = random_prime_number (low_size ,up_size, 5000);
 	long q = random_prime_number (low_size ,up_size , 5000);
 	while ( p == q ){
 		q = random_prime_number (low_size,up_size , 1000);
 	}
 	long n , s , u ;
 	
 	generate_key_values(p ,q ,& n ,& s ,& u ) ;
 	//Pour avoir des cles positives :
 	if (u <0) {
 	long t = (p -1) *( q -1) ;
 	u = u + t ; //on aura toujours s*u mod t = 1
 	}
 	
 	init_key(pKey, s, n);
 	init_key(sKey, u, n);
 	
 	//printf ( " cle publique = (%lx , %lx ) \n" ,s , n ) ;
 	//printf ( " cle privee = (%lx , %lx ) \n" ,u , n ) ;
 }
 
Q3.4 : 
la fonction key_to_str convertit une clé en une chaine de caractère.
l'implémentation de la fonction :
char* key_to_str(Key* key){
	char * res = malloc(sizeof(char)* 100);
	assert(res);
	sprintf(res, "(%lx,%lx)", key->val, key->n);
 	
 	return res;
}
 



la fonction str_to_key convertit une chaine de caractère en une clé
l'implémentation de la fonction :
Key* str_to_key(char* str){
	Key * k = malloc(sizeof(Key));
	assert(k);
	long v , n ;
 	sscanf(str,"(%lx,%lx)",&v, &n);
 	//printf("v=%lx, n=%lx \n", v, n);
 	init_key(k, v, n);
 	
 	return k;
 }

Q3.5 :
definition de la structure Signature
typedef struct signature{
    long *tab;
    int n;
}Signature;



Q3.6 :
la fonction inti_Signature permet d'allouer et  d'initialiser une structure de type signature
implémentation de la fonction :
 Signature* init_signature(long* content, int size){
 	Signature * s = malloc(sizeof(Signature));
 	assert(s);
 	long* tab = malloc(sizeof(long)*size);
 	
 	for(int i=0; i<size; i++){
 		tab[i]=content[i];
 		//printf("tab[%d]=%lx \n", i, tab[i]);
 	}
 	s->tab = tab;
 	s->n = size;
 	
 	return s;
 }
Q3.7 :
la fonction sign qui permet de créer une signature avec un message mess et d'une clé secrete de l'émetteur ( iniialise aussi la structure avec )
l'implémentation de la fonction :
 Signature* sign(char* mess, Key* sKey){
 	long * tab = encrypt(mess, sKey->val, sKey->n);
 	
 	Signature * s = init_signature(tab, strlen(mess));
 	
 	return s;
 }



Q3.9:
la structure de protected
typedef struct Protected{
    Key *pKey;
    char *mess;
    Signature *sgn;
}Protected;
Q3.10 :
la focntion init_protected qui alloue et initialise cette structure 
l'implémentation de la fonction 
Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
	Protected* p = malloc(sizeof(Protected));
	p->pKey = pKey;
	p->mess = strdup(mess);
	p->sgn = init_signature(sgn->tab, sgn->n);              //
	
	return p;
}

Q3.11 :
la fonction verify qui vérifie que la signature contenue dans la structure protected correspond bien au message et à la personne contenus dans la strcutre proctected(qui vérifie si le champs message de la strcutre protected est bien vérifié)

l'implémentation de la fonction :
int verify(Protected *pr){
    char *t=decrypt(pr->sgn->tab,pr->sgn->n,pr->pKey->val,pr->pKey->n);
    char dc[500];
    strcpy(dc,t);
    free(t);
    return strcmp(pr->mess,dc);
}

Q3.12:
la fonction protected_to_str 
l'implémentation de la fonction:
char* protected_to_str(Protected* pr){
	char * res = malloc(sizeof(char)* 100);
	sprintf(res, "%s %s %s", key_to_str(pr->pKey), strdup(pr->mess), signature_to_str(pr->sgn));
 	
 	return res;
}
	


la fonction str_to_protected :
l'implémentation de la fonction:
Protected* str_to_protected(char* str){
	Protected* p = malloc(sizeof(Protected));
	assert(p);
	
	char key[50], mess[50], signature[50];
	
	sscanf(str, "%s %s %s", key, mess, signature);
	
	p->pKey = str_to_key(key);
	p->mess = strdup(mess);
	p->sgn = str_to_signature(signature);
	
	return p;
}


EXO4 : Créaton de données pour simuler le processus de vote 
la fonction generate_random_data  génére un certains nombre de clé en fonction du nombre de candidat et de personne qui vote pour ce candidat ( on a utilisé les fonctions définies précédemment)
l'implémentation de la fonction:
void generate_random_data(int nv,int nc){
    FILE *keys=fopen("keys.txt","w");
    FILE *candidates=fopen("candidates.txt","w");
    FILE *declarations=fopen("declarations.txt","w");
    Key *kptab[nv];
    Key *kstab[nv];
    Key *cptab[nc];
    int nonocc[nc];
    char *mess;
    char *str;
    char *str2;
    int rdm;
    Signature *sgn;
    // Ecriture du fichier keys.txt
    for(int i=0;i<nv;i++){
        kptab[i]=(Key *)malloc(sizeof(Key));
        kstab[i]=(Key *)malloc(sizeof(Key));
        init_pair_keys(kptab[i],kstab[i],3,7);
        str=key_to_str(kstab[i]);
        str2=key_to_str(kptab[i]);
        fprintf(keys,"%s %s\n",str2,str);
        free(str);
        free(str2);
    }
    // Ecriture du fichier candidates.txt
    for(int i=0;i<nc;i++){
        srand(time(NULL)*rand());
        rdm=rand()%nv;
        while(occurence_int(rdm,nonocc,i+1)){
            rdm=rand()%nv;
        }
        cptab[i]=kptab[rdm];
        nonocc[i]=rdm;
        str=key_to_str(cptab[i]);
        fprintf(candidates,"%s\n",str);
        free(str);
    }
    // Ecriture du fichier declarations.txt
    for(int i=0;i<nv;i++){
        srand(time(NULL)*rand());
        int r=rand()%nc;
        char *kpstr=key_to_str(kptab[i]);
        mess=key_to_str(cptab[r]); 
        sgn=sign(mess,kstab[i]);
        str=signature_to_str(sgn);
        fprintf(declarations,"%s %s %s\n",kpstr,mess,str);
        free(str);
        free(mess);
        free(kpstr);
        free_signature(sgn);
    }
    // Libération des clés
    for(int i=0;i<nv;i++){
        free(kstab[i]);
        free(kptab[i]);
    }
    fclose(keys);
    fclose(candidates);
    fclose(declarations);
}


EXO5:lecture et stockage des données des listes chainées
Q5.1:
la fonction create_cell_key qui alloue et initialise une cellule de la liste chainée
l'implémentation de la fonction:
CellKey *create_cell_key(Key *key){
    CellKey *cell=(CellKey *)malloc(sizeof(CellKey));
    cell->data=key;
    cell->next=NULL;
    return cell;
}

Q5.2:
la fonction add_head_cellkey  qui ajoute une clé en tete de liste
l'implémentation de la fonction :
CellKey *add_head_cellkey(CellKey *list,Key *key){
    CellKey *cell=create_cell_key(key);
    cell->next=list;
    return cell;
}
Q5.3:
la fonction read_public_keys retourne une liste chainée contenant toutes les clés publiques du fichier
l'implémentation de la fonction :
CellKey *read_public_keys(char *fichier){
    FILE *f=fopen(fichier,"r");
    
    if (f==NULL){
        printf("ERREUR DE LECTURE,FIN DU PROGRAMME\n");
        exit(1);
    }
    char buffer[256];
    CellKey *list=NULL;
    Key *key;
    long val,n;
    while(fgets(buffer,256,f)!=NULL){
        key=(Key *)malloc(sizeof(Key));
        sscanf(buffer,"(%lx,%lx)",&val,&n);
        init_key(key,val,n);
        list=add_head_cellkey(list,key);
    }
    fclose(f);
    return list;
}

Q5.4:
la fonction print_list_keys affiche une liste chainée de clés, puis utilisez cette fonction pour vérifier la fonction de lecture
l'implémentation de la fonction 
void print_list_keys(CellKey *LCK){
    char *str;
    CellKey *tmp=LCK;
    while(tmp){
        str=key_to_str(tmp->data);
        printf("%s\n",str);
        free(str); 
        tmp=tmp->next;
    }
}

Q5.5:
la fonction delete_cell_key supprime une cellule de la liste chainée de clés.
void delete_cell_key(CellKey *c){
    if (c==NULL){
        return;
    }
    free(c->data);
    free(c);
}
la fonction delete_list_keys supprime une liste chainée de clés
void delete_list_keys(CellKey *list){
    CellKey *tmp;
    while(list){
        tmp=list->next;
        delete_cell_key(list);
        list=tmp;
    }
}

Q5.6:
la fonction create_cell_protected alloue et initialise une cellule de liste chainée.
l'implémentation de la fonction
CellProtected *create_cell_protected(Protected *pr){
    CellProtected *cell=(CellProtected *)malloc(sizeof(CellProtected));
    cell->data=pr;
    cell->next=NULL;
    return cell;
}
Q5.7:
la fonction add_head_cellprotected ajoute une déclaration signée en tete de list
l'implémentation de la fonction
CellProtected *add_head_cellprotected(CellProtected *list,Protected *cpr){
    CellProtected *cell=create_cell_protected(cpr);
    cell->next=list;
    return cell;
}
Q5.8:
la fonction read_protected crée une liste contenant toutes les déclarations signées du fichier declarations.txt
l'implémentation de la fonction
CellProtected *read_protected(){
    FILE *f=fopen("declarations.txt","r");
    if (f==NULL){
        printf("ERREUR DE LECTURE,FIN DU PROGRAMME\n");
        exit(1);
    }
    // Création des tableaux locaux pour la récupération des éléments
    char buffer[512];
    char keystring[256];
    char mess[256];
    char crypted[256];
    // Création des éléments de structures pour créer un élément CellProtected
    Key *pKey=NULL;
    Signature *sgn=NULL;
    Protected *p=NULL;
    CellProtected *list=NULL;
    while (fgets(buffer,512,f)!=NULL){
        sscanf(buffer,"%s %s %s",keystring,mess,crypted);
        pKey=str_to_key(keystring);
        sgn=str_to_signature(crypted);
        p=init_protected(pKey,strdup(mess),sgn);
        list=add_head_cellprotected(list,p);
    }
    fclose(f);
    return list;
}

Q5.9:
la fonction  print_list_protected ajoute une déclaration signée en tete de liste 
l'implémentation de la fonction
void print_list_protected(CellProtected *LCP){
    char *str;
    CellProtected *tmp=LCP;
    while(tmp!=NULL){
        str=protected_to_str(tmp->data);
        printf("%s\n",str);
        free(str);
        tmp=tmp->next;
    }
}
Q5.10:
la fonction delete_cell_protected supprime une cellule de liste chainée de déclaration signées.
l'implémentation 

void delete_cell_protected(CellProtected *c){
    if (c==NULL){
        return;
    }
    free(c->data->mess);
    free(c->data->pKey);
    free(c->data->sgn->tab);
    free(c->data->sgn);
    free(c->data);
    free(c);
}


EXO6:
Q6.1
la fonction tri_decla_valide supprime toutes les déclarations dont la signature n'est pas valide
l'implémentation de la fonction :
CellProtected* tri_decla_valide(CellProtected *liste){
    while(liste){
        CellProtected* tmp=liste;
        CellProtected* tmp2=liste->next;
        if(!verify(liste->data)){
            delete_cell_protected(tmp);
        }
        liste=tmp2;
    }
    return liste;
}


Q6.2
la fonction hashcell alloue une cellule de la table de hachage , et qui initialise ses champs en mettant la valeur à zéro
l'implémentation de la fonction :
HashCell *create_hashcell(Key* key){
    HashCell* cell= (HashCell*) malloc (sizeof(HashCell));
    cell->key=key;
    cell->val=0;
    return cell;
}



Q6.3
la fonction hash_function retourne la postion d'un élément dans la table de hachage
l'implémenation de la fonction 
int hash_function(Key* key, int size){
    return (int) power(key->val,key->n)%size;
}


Q6.4
la fonction find_position cherche l'existanse de la clé publique dan la table de hachage
l'implémentation de la fonction:
int find_position(HashTable* t,Key* key){
    int i;
    int pos = 0;
    for(i=0; i<t->size;i++){
        if(t->tab[i]->key==key){
            if(!pos){
                return 0;
            }
            else{
                return i;
            }
            pos+=1;
        }
    }
    return hash_function(key,pos);
}

Q6.5
la fonction create_hashtable crée et initialise une table de hachage tel que chaque cellule contient une clé 
l'implémentation de la fonction 
HashTable* create_hashtable(CellKey* keys, int size){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size=size;
    table->tab=(HashCell**)malloc(sizeof(HashCell*)*size);
    for(int i=0;i<size;i++){ // Initialisation des éléments à NULL (étant donné que ce n'est pas le cas automatiquement)
        table->tab[i]=NULL;
    }
    while (keys!=NULL){
        int hash=hash_function(keys->data,size);
        if (table->tab[hash]!=NULL){
            for(int i=0;i<size;i++){
                if(table->tab[(hash+i)%size]==NULL){
                    table->tab[(hash+i)%size]=create_hashcell(keys->data);
                    break;
                }
            }
        } else {
            table->tab[hash]=create_hashcell(keys->data);
        }
        keys=keys->next;
    }

    return table;
}

Q6.6
la fonction delete_hashtable supprime une table de hachage 
l'implémentation de la fonction
void delete_hashtable(HashTable* t){
    int i;
    for(i=0;i < t->size; i++){
        if(t->tab != NULL){
            free((void*) t->tab[i]->key);
        }else{
            free((void*) t->tab[i]);
        }
    }
    free(t->tab);
    free(t);
}

Q6.7
la fonction computer_winner calcule le vanqueur de l'élection
l'implémentation de la fonction:
Key *compute_winner(CellProtected *decl,CellKey *candidates,CellKey *voters,int sizeC,int sizeV){
    if ((voters==NULL) || (candidates==NULL) || (decl==NULL) ) {
        return NULL;
    }
    HashTable *tableC=create_hashtable(candidates,sizeC);
    HashTable *tableV=create_hashtable(voters,sizeV);
    CellProtected *declarations=decl;
    while(declarations!=NULL){
        
        if (occurence_key(declarations->data->pKey,voters)){
            // l'electeur a t'il vote?
            if (tableV->tab[find_position(tableV,declarations->data->pKey)]->val==0){ 
                tableV->tab[find_position(tableV,declarations->data->pKey)]->val=1;
                Key *ck=str_to_key(declarations->data->mess);
                // Est-ce que le candidat est légitime ?
                if (occurence_key(ck,candidates)){ 
                    tableC->tab[find_position(tableC,ck)]->val++;
                }
                free(ck);
            }
        }
        declarations=declarations->next;
    }
    HashCell *max=NULL;
    // initialiser le max a la place du premier element hashcell different de NULL trouvé
    for(int i=0;i<sizeC;i++){ 
        if (tableC->tab[i]!=NULL){
            max=tableC->tab[i];
            break;
        }
    }
    // Compare les differente occurence afin de determiner le maximum
    for(int i=1;i<sizeC;i++){
        if ( (tableC->tab[i] != NULL ) && ( (tableC->tab[i]->val) > max->val ) ){
            max=tableC->tab[i];
        }
    }
    Key *res=(Key *)malloc(sizeof(Key));
    init_key(res,max->key->val,max->key->n);
    delete_hashtable(tableC);
    delete_hashtable(tableV);
    
    return res;
}




EXO7:

Q7.1
La fonction write_block ecrit dans un fichier un bloc.
l'implémentation de la fonction:
void write_block(char *nomfic, Block* block){
    FILE *f = fopen(nomfic, "w");
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
    fclose(f);
}
Q7.2
la fonction  read_block qui lit dans un fichier un bloc
l'implémentation de la fonction 
Block* read_block(char* nomfic){
    FILE* f=fopen(nomfic,"r");
    if (!f){
        printf("erreur d'ouverture du fichier %s\n", nomfic);
        return NULL;
    }
    Block* b=(Block*) malloc (sizeof(Block));    
    if(!b){
        printf("erreur d'allocation du block\n");
        fclose(f);
        return NULL;
    }
    char buf[256];
    fgets(buf, 256, f);
    char tmp[256], tmp1[256], tmp2[256], tmp3[256];
    if (sscanf(buf, "%s", tmp)==1)
        b->author=str_to_key(tmp);
    fgets(buf, 256, f);
    if (sscanf(buf, "%s", tmp)==1)
        printf("hash : %s\n", tmp);
        b->hash=strdup(tmp);
        printf("copy : %s\n", b->hash);
    fgets(buf, 256, f);
    if (sscanf(buf, "%s", tmp)==1)
        b->previous_hash=strdup(tmp);
    int i;
    fgets(buf, 256, f);
    if (sscanf(buf, "%d", &i)==1)
        b->nonce=i;
    CellProtected* declarations=(CellProtected*) malloc (sizeof(CellProtected));
    while(fgets(buf, 256, f)){
        if (sscanf(buf, "%s %s %s", tmp1, tmp2, tmp3)==3){
            Protected* pr=str_to_protected(buf);
            add_protected_head(&declarations, pr);
        }
        else{
            printf("erreur de lecture\n");
            fclose(f);
            delete_list_protected(declarations);
            free(b->hash);
            free(b->previous_hash);
            free(b->author);
            free(b);
        }
    } 
    b->votes=declarations;
    fclose(f);
    return b;
}

Q7.3
la fonction block_to_str qui génère une chaine de caractères représentant un bloc.
l'implémentation de la fonction
char* block_to_str(Block* block){
    char* strkey = key_to_str(block->author);
    char noncechar[10];
    sprintf(noncechar, "%d", block->nonce);
    int length = strlen(strkey) + strlen(block->previous_hash) + strlen(noncechar) + 3;
    char* string = (char*)malloc(sizeof(char)*length);
    if(string == NULL){
        printf("Erreur d'allocation de la chaine.\n");
        free(strkey);
        return NULL;
    }
    sprintf(string, "%s\n", strkey);
    // comment on met le unsigned char a la con
    for(int i=0 ; i<SHA256_DIGEST_LENGTH ; i++){
        char tmp[30];
        sprintf(tmp, "%02x", block->previous_hash[i]);
        strcat(string, tmp);
    }
    CellProtected* cell = block->votes;
    while(cell){
        char* votestr = protected_to_str(cell->data);
        length += strlen(votestr)+1;
        string = realloc(string, length);
        strcat(string, "\n");
        strcat(string, votestr);
        cell = cell->next;
        free(votestr);
    }
    strcat(string, "\n");
    strcat(string, noncechar);
    free(strkey);
    return string;
}

Q7.4
installer la bibliothèque openssl
Q7.5
fonction  hash_char  prend une chaˆıne
de caractères, et retourne sa valeur hachéee obtenue par l’algorithme SHA256
l'implémentation
unsigned char* hash_char(char* chaine){
    return SHA256(chaine, strlen(chaine), 0);
} 
Q7.6
compute_prof_of_work réalise les opérations demandées.
void compute_proof_of_work(Block *B, int d){
    B->nonce = 0;
    while(1){
        char* blockstr = block_to_str(B);
        unsigned char* hashed = hash_char(blockstr);
        int i=0;
        while(i < d){
            if(hashed[i]=='0'){
                i++;
            }
            else{
                (B->nonce)++;
                break;
            }
        }
        if (i==d) break;
    }
}
Q7.7
la fonction verify_block vérifie qu'un bloc est valide 
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
Q7.8
étudier le temps moyen de la fonction computer_proof_of_work selon la valeur de d.
la valeur de d à partir de laquelle ce temps dépasse une séconde est d=
Q7.9
la fonction delete_block supprime un bloc
l'implémentation de la fonction:
void delete_block(Block* b){
    free(b->hash);
    free(b->previous_hash);
    CellProtected *tmp;
    while(b->votes){
        tmp = b->votes->next;
        free(b->votes);
        b->votes = tmp;
    }
    free(b);
}










 
