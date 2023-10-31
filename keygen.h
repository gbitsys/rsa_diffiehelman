#include<gmp.h>
void keygen(mpz_t p,mpz_t q, mpz_t keyLength, mpz_t result);
int checkOdd(mpz_t p);
int readNum();
void epsilonGen(mpz_t lamda, mpz_t length,mpz_t result);
void primeGen(mpz_t start, mpz_t end, mpz_t result);
