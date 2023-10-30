#include<stdio.h>
#include"keygen.h"

int main(){
  mpz_t key;
  mpz_init(key);
	keygen(7,11,5, key);
  return 0;
}
