#include"keygen.h"


void keygen(mpz_t p, mpz_t q, mpz_t keyLength, mpz_t result[])
{
  //declaring variables suitable with gmp stdlib
  mpz_t key, n, lamda, epsilon;

  //initializing them
  mpz_inits(key, n, lamda, epsilon, NULL);
	mpz_set_si(key, 0);

  printf("[DEBUG] keygen start\n");
  gmp_printf("[DEBUG] Key length: %Zd\n", keyLength);

	if (checkOdd(p)==0 || checkOdd(q)==0)
		return ; //we can't generate a key for non prime numbers

 //calculating n using gmp library functions 
  mpz_mul(n, p, q); //n = p*q
  mpz_sub_ui(p,p,1); //p=(p-1)
  mpz_sub_ui(q,q,1); //q=(q-1)
  mpz_mul(lamda, p, q); //lamda(n)=(p-1)(q-1) euler's totient function
  
	epsilonGen(lamda, keyLength,epsilon);

  mpz_invert(key, epsilon, lamda);
  gmp_printf("[DEBUG] d = %Zd\n", key);
  mpz_clears(key, n, epsilon, lamda, NULL); //preventing memory leak

}

//this function generates random prime number within a range
void primeGen(mpz_t start, mpz_t end, mpz_t result){
}

int checkOdd(mpz_t p)
{
  mpz_t result;
  mpz_init(result);
  mpz_mod_ui(result, p, 2);
	if (mpz_get_si(result)==0)
		return 0;//false 
	return 1;//true
}

//generates a random epsilon number where (e % lambda(n) != 0) AND (gcd(e, lambda) == 1)
void epsilonGen(mpz_t lamda, mpz_t length, mpz_t result)
{
  //initializing variables
  //temp is used just for storing calculations
  //index is the epsilon we calculate
	mpz_t index, gcdResult, temp;
  mpz_inits(index, gcdResult, temp, NULL);
  printf("[DEBUG] inside epsilonGen\n");
  
  gmp_printf("[DEBUG] index: %Zd\n", index);

  for (;;){
    mpz_gcd(gcdResult, index, lamda);
        mpz_mod(temp, index, lamda); //performing index%lamda
    if (mpz_cmp_si(temp, 0)!=0  && mpz_get_si(gcdResult)==1 && mpz_cmp_si(index, 1)!=0) 
      break;
    //sizeof(length)==mpz_sizeinbase(index, 2)
    mpz_add_ui(index,index, 1);
	}
  gmp_printf("[DEBUG] epsilon: %Zd\n", index);
  mpz_set(result, index);
  mpz_clears(index, gcdResult, temp, NULL);
}
