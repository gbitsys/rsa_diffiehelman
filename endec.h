#include<gmp.h>
#include<stdlib.h>
#include<stdio.h>

FILE* encryptDataDH(char *message, mpz_t key[]); //reads message from file encrypt and generates cipher text
FILE* decryptDataDH(char *message, mpz_t key[]); //vise versa

void encryptDataRSA(char *message, mpz_t key[]);
void decryptDataRSA(char *message, mpz_t key[]);
