#include<stdio.h>
#include"keygen.h"

int main(int argc, char *argv[]){
  mpz_t key, p, q, keyLength;

  mpz_inits(key, p, q, keyLength, NULL);
  int base = 10;
  char *pStr = "56788324123";
  char *qStr = "18132231211";
  
  mpz_set_str(p, pStr, base);
  mpz_set_str(q, qStr, base);
  mpz_set_si(keyLength, mpz_sizeinbase(p,2)+mpz_sizeinbase(q,2));
	keygen(p, q,keyLength, key);
  return 0;
}
