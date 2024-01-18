/*main EXO1\Exo2*/ 

#include "exo1.h"
#include "exo2.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void print_lv(long *result,int size){
    printf("Vector: [");
    for(int i=0;i<size;i++){
        printf("%lx \t",result[i]);
    }
    printf("]\n");
}


int main(){
		//Exo1 :

    for(int i=0;i<100;i++){
    srand(time(NULL)*rand());


    // Generation de cle :
    long p=random_prime_number(3,7,5000);
    long q=random_prime_number(3,7,5000);
    while(p==q){
        q=random_prime_number(3,7,5000);
    }
    long n,s,u;
    generate_key_values(p,q,&n,&s,&u);
    // Pour avoir des cles positives : 
    if (u<0){
        long t=(p-1)*(q-1);
        u=u+t; // On aura toujours s*u mod t=1
    }

    // Affichage des cles en hexadecimal
    printf("cle publique = (%lx,%lx) \n",s,n);
    printf("cle privee = (%lx,%lx) \n",u,n);

    // Chiffrement :
    char mess[10]="Hello";
    int len=strlen(mess);
    long *crypted=encrypt(mess,s,n);

    printf("Initial message: %s \n",mess);
    printf("Encoded representation : \n");
    print_lv(crypted,len);

    // Dechiffrement
    char *decoded=decrypt(crypted,len,u,n);
    printf("Decoded: %s\n",decoded);
    free(decoded);
    free(crypted);
    }

    clock_t ti,tf;
    double tcpu1,tcpu2;

    /*int i=3;
    while (tcpu1<2.0)    {
        ti = clock();
        is_prime_naive(i);
        tf=clock();

        tcpu1==(double)((tf-ti)/CLOCKS_PER_SEC*1000);
        i==2;
    }
    printf("Temps pour testser %d : %f ms\n",i , tcpu1);
    */
    FILE *mp=fopen("sortir_modpow.txt","w");
    if (! mp){
        printf("Erreur à l'ouverture du fichier\n");
        return -1;
    }
    long a =6;
    long n_=57;
    for (long m=10;m<10000;m=m+10){
        ti=clock();
        modpow_naive(a,m,n_);
        tf=clock();
        tcpu1=((double)(tf-ti))/CLOCKS_PER_SEC;
        ti=clock();
        modpow(a,m,n_);
        tf=clock();
        tcpu2=((double)(tf-ti))/CLOCKS_PER_SEC;
        fprintf(mp,"%ld %f %f\n",m,tcpu1*10000,tcpu2*1000);
    }
    fclose(mp);
		
        return 0 ;
    }

		
