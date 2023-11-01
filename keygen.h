#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
void keygen(mpz_t p,mpz_t q, mpz_t keyLength, mpz_t result[]); //generating RSA key-pair 
int checkOdd(mpz_t p); //checks if a mpz_t number is odd
int readNum();
void epsilonGen(mpz_t lamda, mpz_t length,mpz_t result); //generating RSA encryption key
void primeGen(mpz_t start, mpz_t end, mpz_t result);
