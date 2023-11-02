#include<gmp.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//insert a message (name of file), an encryption key [n, e] receive encrypted message (RSA)
//key[0] = n, key[1] = e
void encryptDataRSA(char * message, mpz_t key[]){
	FILE *fp;
    FILE *output;
    char *fName = "cipheredRSA.txt";
	int len = 0;
	char c;
    output = fopen(fName, "w");
    //gmp_printf("[DEBUG] n=%Zd e=%Zd\n",key[0], key[1]);
	//in case something goes wrong
	if (output ==NULL){
		printf("File error!!!\n");
		return;
	}

    char *messageStr = "pavlo gamiesai"; //this variable used to read text from the file 
    mpz_t ciphChar, msgChar;
    mpz_inits(msgChar, ciphChar, NULL);
    int i=0;
    for(i=0;i<(int)strlen(messageStr);i++)
    {
        //printf("hello world\n");
        char c = messageStr[i]; //reading char one by one 
        mpz_set_si(msgChar, (int)c);
        mpz_powm(ciphChar, msgChar, key[1], key[0]); // m = c^d mod n
        gmp_fprintf(output, "%Zd\n", ciphChar);
        //break;
    }
   
    //printf("[DEBUG]message is: %s\n", messageStr);

    

    //preventing memory leaks
    mpz_clears(msgChar, ciphChar, NULL);
    fclose(output);
} ;

void decryptDataRSA(mpz_t key[]){
	FILE * input;
    FILE *output;
	int len = 0;
    char *fName = "decipheredRSA.txt";

	input = fopen("cipheredRSA.txt", "r");
    output = fopen(fName, "w");
	//in case something goes wrong with files
	if (input==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}

    mpz_t ciphChar, msgChar;
    int ciphInt;
    mpz_inits(ciphChar, msgChar, NULL);
    //printf("hello\n");
    while (!feof(input))
    {   
        mpz_inp_str(ciphChar, input, 10);
        //gmp_printf("%Zd\n", ciphChar);
        mpz_powm(msgChar, ciphChar, key[1], key[0]); // m = c^d mod n
        //gmp_printf("%Zd\n", msgChar);
        gmp_printf("%c\n", (char)mpz_get_si(msgChar));
        //fprintf(output, "%c", (int)mpz_get_si(msgChar));
        //fprintf(stdout, "%c\t", (char)ciphInt);
        //i++;
    }
    printf("\n");
    mpz_clears(ciphChar, msgChar, NULL);
    fclose(input);
    fclose(output);
} ;

int main(){

    mpz_t key[2];
    mpz_inits(key[0], key[1], NULL);
    mpz_set_si(key[0], 3233);
    mpz_set_si(key[1], 17);
    char* text = "message.txt";
    encryptDataRSA(text, key);

    mpz_t keyt[2];
    mpz_inits(keyt[0], keyt[1], NULL);
    mpz_set_si(keyt[0], 3233);
    mpz_set_si(keyt[1], 413);

    decryptDataRSA(keyt);

    return 0;
}
