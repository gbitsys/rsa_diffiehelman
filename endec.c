#include"endec.h"

FILE* encryptDataDH(char * message, mpz_t key[]){
	return NULL;
} 

//insert a message (name of file), an encryption key [n, e] receive encrypted message (RSA)
//key[0] = n, key[1] = e, key[2]=d
void encryptDataRSA(char * message, mpz_t key[]){
	FILE * fp;
    FILE *output;
    char *fName = "cipheredRSA2.txt";
	int len = 0;
	char c;
	fp = fopen(message, "r");
    output = fopen(fName, "w");
	//in case something goes wrong
	if (fp==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)
    fseek(fp, 0, SEEK_SET);

    char *messageStr; //this variable used to read text from the file 
    messageStr = malloc(sizeof(char)*len);
    mpz_t ciphChar, msgChar;
    mpz_inits(msgChar, ciphChar, NULL);
    int i=0;
    while (i<len)
    {
        c = fgetc(fp);
        messageStr[i++] = (char) c; //reading char one by one 
        mpz_set_ui(msgChar, (unsigned int)c);
        mpz_powm(ciphChar, msgChar, key[1], key[0]); // m = c^d mod n
        gmp_fprintf(output, "%Zd\n", ciphChar);

    }
    messageStr[i]='\0';
   
    //preventing memory leaks
    mpz_clears(msgChar, ciphChar, NULL);
    free(messageStr);
    fclose(output);
    fclose(fp);

} 

FILE* decryptDataDH(char* message, mpz_t key[]){

	return NULL;
} 

void decryptDataRSA(char* message, mpz_t key[]){
	FILE * fp;
    FILE *output;
    char *fName = "cipheredRSA2.txt";
    char *outputName = "decipheredRSAw.txt";
    int len = 0;
	fp = fopen(fName, "r");
    output = fopen(outputName, "w");
	//in case something goes wrong with files
	if (fp==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}
	
    fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)
    fseek(fp, 0, SEEK_SET);

    mpz_t ciphChar, msgChar;
    mpz_inits(ciphChar, msgChar, NULL);
    int i=0;
    while (!feof(fp))
    {
        mpz_inp_str(ciphChar, fp, 10);
        mpz_powm(msgChar, ciphChar, key[2], key[0]); // m = c^d mod n
        gmp_fprintf(output, "%c", (char)mpz_get_ui(msgChar));
    }
    gmp_fprintf(output, "%c", '\n');
    //preventing memory leaks 
    mpz_clears(ciphChar, msgChar, NULL);
    fclose(fp);
    fclose(output);
} 
