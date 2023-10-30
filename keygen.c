#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include"keygen.h"
#include<stdlib.h>

void keygen(int p, int q, int keyLength, mpz_t result)
{
  //declaring variables suitable with gmp stdlib
  mpz_t key, n, lamda, epsilon, pm, qm;

  //initializing them
  mpz_inits(key, n, lamda, epsilon, pm, qm, NULL);
  mpz_set_si(pm, p);
  mpz_set_si(qm, q);
	mpz_set_si(key, 0);

  printf("[DEBUG] keygen start\n");

	if (checkOdd(pm)==0 || checkOdd(qm)==0)
		return ; //we can't generate a key for non prime numbers

 //calculating n using gmp library functions 
  mpz_mul(n, pm, qm); //n = p*q
  mpz_sub_ui(pm,pm,1); //p=(p-1)
  mpz_sub_ui(qm,qm,1); //q=(q-1)
  mpz_mul(lamda, pm, qm); //lamda(n)=(p-1)(q-1) euler's totient function
  
	epsilonGen(lamda, epsilon);

  mpz_clears(key, n, epsilon, lamda, pm, qm, NULL);

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
void epsilonGen(mpz_t lamda, mpz_t result)
{
  //initializing variables
	mpz_t index, gcdResult, temp;
  mpz_inits(index, gcdResult, temp, NULL);
  printf("[DEBUG] inside epsilonGen\n");
  
  gmp_printf("[DEBUG] index: %Zd\n", index);

  for (;;){
    mpz_gcd(gcdResult, index, lamda);
    gmp_printf("[GCD] gcd: %Zd\t", gcdResult);
    gmp_printf("[DEBUG] index in loop: %Zd\n", index);
    mpz_mod(temp, index, lamda); //performing index%lamda
    if ( mpz_cmp_si(temp, 0)!=0  && mpz_get_si(gcdResult)==1 && mpz_cmp_si(index, 1)!=0)
      break;
    mpz_add_ui(index,index, 1);
	}
  
  mpz_set(result, index);
  mpz_clears(index, gcdResult, temp, NULL);
}
