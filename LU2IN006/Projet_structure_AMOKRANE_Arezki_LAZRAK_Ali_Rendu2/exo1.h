#ifndef EXO1_H
#define EXO1_H

long power(long a , int b);
int is_prime_naive(long n);
long  modpow_naive(long a , long m , long n);
int modpow(long a , long m , long n );
int witness(long a , long b , long d , long p);
long rand_long(long ls , long  us);
int is_prime_miller(long p , int k );
long random_prime_number(int ls , int us , int k );

#endif