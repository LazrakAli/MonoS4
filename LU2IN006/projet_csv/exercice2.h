#ifndef __EXERCICE_2__
#define __EXERCICE_2__

typedef struct cell{
    char * data;
    struct cell* next;
}Cell;
typedef Cell* List;

List* initList();//initialise la List
Cell* buildCell(char* ch);//construit une cell
void insertFirst(List *L, Cell* C);//insert entete C dans la list L
char* ctos(Cell* c);//retourne la chaine composer de cell
char* ltos(List* L);//concatene la liste dans une chaine avec comme separateur |
Cell* listGet(List* L, int i);//renvoie l'element a la position i
Cell* searchList(List* L, char* str);//cherche dans la liste un element le renvoie s'il y est ou NULL
List* stol(char* s);//l'inverse de ltos prend une chaine de char est en fait une liste
void ltof(List* L, char* path);// permettant d'ecrire une liste dans un fichier
List *ftol (char *path);//permet de lire une liste enregistée dans un fichier
#endif