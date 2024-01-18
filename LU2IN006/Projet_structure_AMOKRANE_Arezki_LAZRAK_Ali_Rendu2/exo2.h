#ifndef EXO2_H
#define EXO2_H


long extended_gcd(long s, long t, long *u, long *v);
void generate_key_values(long p, long q, long* s, long *n, long *u);
long* encrypt(char* chaine, long s, long n);
char* decrypt(long* crypt, int size, long u, long n);

#endif