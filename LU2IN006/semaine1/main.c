#include <stdlib.h>
#include <stdio.h>

int fact(int n ){
    int res=0;
    printf("appelle de fact avec n =%d\n",n);
    if (n==0) return 1;
    else res=n*fact(n-1);
    printf("resultat pour n=%d : res =%d\n",n,res);
    return res;
}

int main (void){
int l=fact(5);
return 0;
}
