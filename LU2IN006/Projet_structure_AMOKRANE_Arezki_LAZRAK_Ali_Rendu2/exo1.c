//AMOKRANE Arezki 28610421
// LAZRAK Ali 28605235
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "exo1.h"

// Fonction  qui calcule a puissance b
long power(long a , int b)
{
	if(b<0)
	{
		return 0;
	}
	if(b==0)
	{
		return 1;
	}
	long pow;
	pow = power(a , b/2);	
	if(b%2 == 0)
	{
		return pow*pow;
	}

	else
	{
		return pow*pow * a;
	}
}

//TESTS DE PRIMALITE

int is_prime_naive(long n)
{
	if (n%2==0) return 0;
	for(int i=3;i<n-1;i++)  
	{
		if( n%i==0) //Dans ce cas i divise n, ce qui implique que p n'est pas premier 
		{
			return 0; 
		}

	}
	//COMPLEXITE de cette algorithme  est O(n)

	return 1;

}

// calcule a 'à la puissance' m 'modulo' n
long  modpow_naive(long a , long m , long n)
{
	long res = 1;
	for(int i = 0 ; i<=m ; i++) 
	{
		res =  (res*a) % n  ;	
	}
	return res  ;
//COMPLEXITE de cette algorithme O(m)
}

//fonction réalisant des succession d'élévation au carré
int modpow(long a , long m , long n )
{
	if(m==0)
	{
		return a; // retourne a quand m=0 
	}

	if (m<=1){
		return a%n; // 
	}

	long b=modpow(a , m/2 , n);
	if(m%2 == 0){
		return (b*b) % n; // return  b*b mod n quand m est pair
	}
	else
	{
		return (a*b*b) % n ; // return a*b*b , quand m est impaire 
	}
}


int witness ( long a , long b , long d , long p ) {
    long x = modpow (a ,d , p ) ;
    if( x == 1) {
        return 0;
    }
    for( long i = 0; i < b ; i ++) {
        if( x == p -1) {
            return 0;
        }
    x = modpow (x ,2 , p ) ;
    }
    return 1;
}
// génére un entier long aléatoirement entre low et up 
long rand_long ( long ls , long us ) {
    return rand () % ( us - ls +1) + ls ;
}
// la fonction réaliser le test de Miller_Rabin
int is_prime_miller (long p,int k ) {
    if (p==2) {
        return 1;
    }
    if (!(p&1) || p<=1) { //on verifie que p est impair et different de 1
        return 0;
    }
    //on determine b et d :
    long b = 0;
    long d = p-1;
    while (!(d&1)) { //tant que d n’est pas impair
        d = d /2;
        b = b +1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for(i=0;i<k;i++) {
        a=rand_long(2,p-1);
        if(witness(a,b,d,p)) {
            return 0;
        }
    }
    return 1;
}


// Fonction retourne un nombre premier de taille comprisse entre low_size et up_size.
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
