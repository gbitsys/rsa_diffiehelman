#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void generateRSAKeyPair(mpz_t given_len);
void encrypt(char* input, char* output, char* keyf);
void decrypt(char* input, char* output, char* keyf);
void performance(char *input, char *cipherTxt, char *decipherTxt);
void keyFile(char *fileName, mpz_t keys[]);
