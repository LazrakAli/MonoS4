#include <stdlib.h>
#include <stdio.h>


typedef struct element{
    int val;
    int cle;
    struct element *suiv;
}Element;

typedef struct _tableHachage{
    Element **T;
    int tailleTableau;
}TableHachage;

TableHachage *t=malloc(sizeof(TableHachage));
t->T=malloc(taille*sizeof(Element));
t->tailleTableau=taille;
for (int i=0,i<taille;i++){
    t->T[i]=NULL;
}


void insert(Table Hashage *t,int cle,int val){
    Element *e=malloc(sizeof(Element));
    e->val=val;
    e->cle=cle;
    Element *e1=t->T[g(cle)];
    t->T[g(cle)]=e;
    e->suiv=e1;
}

/*
j'ai n elements<-(cle,valeur) dans ma tbale;
Complexite pour compter le nombre d'elements:
    O(TailleTableau+n);
*/
/*
Q 2.1)

mot u           clé f(u) en héxa        f(cle) ()         g(cle)  

le              FF2E                    E                 14
cours           178DD38                 8                 8
appele          75EA33                  3                 3
structures      35CE5                   5                 5
de              9AA8BF1                 1                 1
données         2738                    8                 8
est             A4C74                   4                 4
absolument      1CA4C74                 4                 4
génial          14D26                   6                 6
j'adore         5A38                    8                 8
faire           1BAE5                   5                 5
ses             65B4EE5                 5                 5
TD/TME          8C74                    4                 4



Exercice 3:

Q 2)
f2 redra toujours 0
f3 rendra toujours des nombre paires donc on perd au moins la moitie de notre espace
f4 mod(10) plus probleme si dessus


*/

int main(){
    int x=1;
    if (x==0)?(x=0):(x+=2);
    printf("x=%d\n",x);
    return 0;
}