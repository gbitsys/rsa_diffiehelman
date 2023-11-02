#include"keygen.h"


void keygen(mpz_t p, mpz_t q, mpz_t result[])
{
  //declaring variables suitable with gmp stdlib
  mpz_t delta, n, lamda, epsilon;

  //initializing them
  mpz_inits(delta, n, lamda, epsilon, NULL);
	mpz_set_si(delta, 0);

  printf("[DEBUG] keygen start\n");

	if (checkPrime(p)==0 || checkPrime(q)==0)
		return ; //we can't generate a key for non prime numbers

 //calculating n using gmp library functions 
  mpz_mul(n, p, q); //n = p*q
  mpz_sub_ui(p,p,1); //p=(p-1)
  mpz_sub_ui(q,q,1); //q=(q-1)
  mpz_mul(lamda, p, q); //lamda(n)=(p-1)(q-1) euler's totient function
  
	epsilonGen(lamda, epsilon);

  mpz_invert(delta, epsilon, lamda);
  mpz_set(result[0], n); //result[0]=n
  mpz_set(result[1], epsilon); //result[1]=e
  mpz_set(result[2], delta); //result[2]=d
 //gmp_printf("[DEBUG] delta = %Zd\n", delta);
  mpz_clears(delta, n, epsilon, lamda, NULL); //preventing memory leak

}

//given a key length this function generates key pair for RSA
void randomPair(int bitLength, mpz_t result[]){
  //generate randomness!?
  gmp_randstate_t state;
  mpz_t p, q, randomNum;
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, time(NULL));
  mpz_inits(p,q,randomNum, NULL);

  do{
    mpz_urandomb(randomNum, state, bitLength); //generate odd number (p)
    mpz_nextprime(p, randomNum);
    mpz_urandomb(randomNum, state, bitLength); //generate odd number (q)
    mpz_nextprime(q, randomNum);
  }while(mpz_cmp(p,q)==0);

 /* gmp_printf("Random mpz_t of %d bits: %Zd\n", bitLength, p);
  gmp_printf("Random mpz_t of %d bits: %Zd\n", bitLength, q);*/

  keygen(p, q, result);
  //cleaning
  gmp_randclear(state);
  mpz_clears(p, q, randomNum,NULL);

}

int checkPrime(mpz_t p)
{
  mpz_t result;
  mpz_init(result);
  mpz_gcd_ui(result,p,1);
	if (mpz_odd_p(p)!=0 && mpz_cmp_si(result, 1)==0)
  mpz_clear(result);
		return 1;//true
  mpz_clear(result);
	return 0;//false
}

//generates a random epsilon number where (e % lambda(n) != 0) AND (gcd(e, lambda) == 1)
void epsilonGen(mpz_t lamda, mpz_t result)
{
  //initializing variables
  //temp is used just for storing calculations
  //index is the epsilon we calculate
	mpz_t index, gcdResult, temp;
  mpz_inits(index, gcdResult, temp, NULL);
  printf("[DEBUG] inside epsilonGen\n");
  
 //gmp_printf("[DEBUG] index: %Zd\n", index);

  for (;;){
    mpz_gcd(gcdResult, index, lamda);
    mpz_mod(temp, index, lamda); //performing index%lamda
    if (mpz_cmp_si(temp, 0)!=0  && mpz_cmp_si(gcdResult, 1)==0 && mpz_cmp_si(index, 1)!=0) 
      break;
    //sizeof(length)==mpz_sizeinbase(index, 2)
    mpz_add_ui(index,index, 1);
	}
  //gmp_printf("[DEBUG] epsilon: %Zd\n", index);
  mpz_set(result, index);
  mpz_clears(index, gcdResult, temp, NULL);
}
