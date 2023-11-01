#include"endec.h"

FILE* encryptDataDH(char * message, mpz_t key[]){
	return NULL;
} 

//insert a message (name of file), an encryption key [n, e] receive encrypted message (RSA)
//key[0] = n, key[1] = e
void encryptDataRSA(char * message, mpz_t key[]){
	FILE * fp;
    FILE *output;
    char *fName = "cipheredRSA2.txt";
	int len = 0;
	char c;
	fp = fopen(message, "r");
    output = fopen(fName, "w");
    gmp_printf("[DEBUG] n=%Zd e=%Zd\n",key[0], key[1]);
	//in case something goes wrong
	if (fp==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)
    fseek(fp, 0, SEEK_SET);

    char *messageStr, *cipherStr; //this variable used to read text from the file 
    messageStr = malloc(sizeof(char)*len);
    cipherStr = malloc(sizeof(char)*len);
    mpz_t ciphChar, msgChar;
    mpz_inits(msgChar, ciphChar, NULL);
    int i=0;
    while (i<len)
    {
        c = fgetc(fp);
        messageStr[i] = (char) c; //reading char one by one 
        mpz_set_ui(msgChar, (unsigned int)c);
        mpz_powm(ciphChar, msgChar, key[1], key[0]); // m = c^d mod n
        gmp_printf("%Zd\n", ciphChar);
        cipherStr[i++]=(char)mpz_get_ui(ciphChar);
        //gmp_fprintf(output, "%Zd\n", ciphChar);
        fprintf(output, "%u ", (unsigned)mpz_get_ui(ciphChar));

    }
    messageStr[i]='\0';
    cipherStr[i]='\0';
   
    printf("[DEBUG]message is: %s\n", messageStr);

    

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
	int len = 0;
    char *fName = "cipheredRSA2.txt";
    char *outputName = "decipheredRSA.txt";

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
    char ciphInt;
    mpz_inits(ciphChar, msgChar, NULL);

    for (int i=0; i<len; i++)
    {
        ciphInt = fgetc(fp);
        //fscanf(fp, "%c ", &ciphInt);
        //gmp_fscanf(fp, "%Zd\n", &ciphChar);
        gmp_printf("%Zd\n", ciphChar);
        //mpz_set_si(ciphChar, ciphInt);
        mpz_set_ui(ciphChar, (unsigned int)ciphInt);
        mpz_powm(msgChar, ciphChar, key[1], key[0]); // m = c^d mod n
        fprintf(stdout, "%c", (char)mpz_get_ui(msgChar));
        i++;
    }
    printf("\n");

    mpz_clears(ciphChar, msgChar, NULL);
    fclose(fp);
    fclose(output);
} 