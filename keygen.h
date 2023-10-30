#include<gmp.h>
void keygen(int p, int q, int keyLength, mpz_t result);
int checkOdd(mpz_t p);
int readNum();
void epsilonGen(mpz_t lamda, mpz_t result);
