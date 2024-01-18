//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include "exo5.h"
#include "exo2.h"
#include "exo1.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Fonction d'affichage d'un tableau de long
void print_long_vector(long *result,int size){
    printf("Vector: [");
    for(int i=0;i<size;i++){
        printf("%lx \t",result[i]);
    }
    printf("]\n");
}
//Fonction d'affichage d'une liste de clés
void print_list_keys(CellKey *LCK){
    char *str;
    CellKey *q=LCK;
    while(q){
        str=key_to_str(q->data);
        printf("%s\n",str);
        free(str); 
        q=q->next;
    }
}
//Fonction de création d'un élément CellKey
CellKey *create_cell_key(Key *key){
    CellKey *cell=(CellKey *)malloc(sizeof(CellKey));
    cell->data=key;
    cell->next=NULL;
    return cell;
}
///Fonction de création d'un élément CellProtected
CellProtected *create_cell_protected(Protected *pr){
    CellProtected *cell=(CellProtected *)malloc(sizeof(CellProtected));
    cell->data=pr;
    cell->next=NULL;
    return cell;
}
//Fonction d'ajout de Key en tete dans une liste de clés (CellKey)
CellKey *en_tete_cellkey(CellKey *list,Key *key){
    CellKey *cell=create_cell_key(key);
    cell->next=list;
    return cell;
}
//Fonction d'ajout en tête d'une déclaration (Protected) dans une liste de déclarations (CellProtected)
CellProtected *en_tete_cellprotected(CellProtected *list,Protected *cpr){
    CellProtected *cell=create_cell_protected(cpr);
    cell->next=list;
    return cell;
}
//Fonction de lecture de clés publiques
CellKey *read_public_keys(char *fichier){
    FILE *f=fopen(fichier,"r"); // ouverture du fichier 
    
    if (f==NULL){
        printf("Erreur de l'écture du fichier \n");
        exit(1);
    }
    char buffer[256]; // buffer
    CellKey *list=NULL;
    Key *key;
    long val,n;
    while(fgets(buffer,256,f)!=NULL){ // Lecture ligne par ligne dans le fichier 
        key=(Key *)malloc(sizeof(Key));
        sscanf(buffer,"(%lx,%lx)",&val,&n);
        init_key(key,val,n);
        list=en_tete_cellkey(list,key); // ajouter la clé lu en tete de liste
    }
    fclose(f); //Fermeture du fichier 
    return list;
}
//Fonction de suppression d'un cellule de liste de clés (CellKey)
void delete_cell_key(CellKey *c){
    if (c==NULL){
        return;
    }
    free(c->data);
    free(c);
}
//Fonction de suppression de liste de clés (CellKey)
void delete_list_keys(CellKey *list){
    CellKey *q;
    while(list){
        q=list->next;
        delete_cell_key(list);
        list=q;
    }
}
//Fonction d'affichage de liste de déclarations (CellProtected)
void print_list_protected(CellProtected *LCP){
    char *str;
    CellProtected *q=LCP;
    while(q!=NULL){
        str=protected_to_str(q->data);
        printf("%s\n",str);
        free(str);
        q=q->next;
    }
}
// Fonction de lecture de keys.txt et declarations.txt pour créer une liste de déclarations (CellProtected)
CellProtected *read_protected(){
    FILE *f=fopen("declarations.txt","r");
    if (f==NULL){
        printf("Erreur de l'écture du fichier\n");
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
    while (fgets(buffer,512,f)!=NULL){ // Lecture ligne par ligne 
        sscanf(buffer,"%s %s %s",keystring,mess,crypted);
        pKey=str_to_key(keystring);
        sgn=str_to_signature(crypted);
        p=init_protected(pKey,strdup(mess),sgn);
        list=en_tete_cellprotected(list,p);
    }
    fclose(f); // fermeture du fichier
    return list;
}

//Fonction de suppression d'une cellule CellProtected
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

//Fonction de suppression d'une liste de CellProtected
void delete_list_protected(CellProtected *list){
    CellProtected *q;
    while (list!=NULL){
        q=list->next;
        //free(list->data->mess);
        delete_cell_protected(list);
        list=q;
    }
}

void fusion_cell_protected(CellProtected **first, CellProtected *second){
    if (*first==NULL){
        *first=second;
        return;
    }
    CellProtected *tmp=*first;
    while(tmp->next!=NULL){
        tmp=tmp->next;
    }
    tmp->next=second;
}

//Fonction retirant toutes les déclarations non valides (Fausses signatures)
CellProtected *valid_list_protected(CellProtected *list){
    CellProtected *prec;
    CellProtected *cour;
    CellProtected *q;
    if (verify(list->data)!=0){
        q=list;
        list=list->next;
        delete_cell_protected(q);
        return valid_list_protected(list);
    }
    prec=list;
    cour=list->next;
    while (cour!=NULL){
        if (verify(cour->data)!=0){
            q=cour;
            cour=cour->next;
            prec->next=cour;
            delete_cell_protected(q);
        } else {
            prec=prec->next;
            cour=cour->next;
        }
    }
    return list;
}
char *CPlist_to_str(CellProtected *list){
	    CellProtected *q=list;
	    char *res=malloc(sizeof(char));
	    char *qtmp;
	    int taille=sizeof(char);
	    while(q!=NULL){
	        qtmp=protected_to_str(q->data);
	        taille+=strlen(qtmp)+1;
	        res=realloc(res,taille);
	        q=q->next;
	        free(qtmp);
	    }
	    return res;
	}
