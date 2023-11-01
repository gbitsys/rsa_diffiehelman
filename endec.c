#include"endec.h"

FILE* encryptDataDH(char * message, mpz_t key[]){
	return NULL;
} 

//insert a message (name of file), an encryption key [n, e] receive encrypted message (RSA)
//key[0] = n, key[1] = e
void encryptDataRSA(char * message, mpz_t key[]){
	FILE * fp;
	int len = 0;
	char c;
	fp = fopen(message, "r");
    gmp_printf("[DEBUG] n=%Zd e=%Zd\n",key[0], key[1]);
	//in case something goes wrong
	if (fp==NULL){
		printf("File error!!!\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)

    fseek(fp, 0, SEEK_SET);
    char *messageStr; //this variable used to read text from the file 
    messageStr = malloc(sizeof(char)*len);

    int i=0;
    while ((c = fgetc(fp)) != EOF)
    {
        messageStr[i++] = (char) c; //reading char one by one 
    }
    messageStr[i]='\0';

    //done with reading 

    //calculations 
    printf("Encrypting ...\n");
    FILE* outputFile = fopen("cipheredRSA.txt", "w");
    if (outputFile == NULL) {
        printf("File creation error!!!\n");
        free(messageStr);
        fclose(fp);
        return;
    }
   
    printf("[DEBUG]message is: %s\n", messageStr);
 	i=0;
    mpz_t msgChar, ciphChar;
    mpz_inits(msgChar, ciphChar, NULL);

    do{
    	mpz_set_ui(msgChar, messageStr[i]);
    	mpz_powm(ciphChar, msgChar, key[1], key[0]); //c = m^e mod n
    	//gmp_fprintf(outputFile, "%Zd", ciphChar);
        fprintf(outputFile, "%u", (unsigned int)mpz_get_ui(ciphChar));
        printf("%u\t", (unsigned int)mpz_get_ui(ciphChar));
    	i++;
    }while(i<len);
    printf("\n");
    //preventing memory leaks
    mpz_clears(msgChar, ciphChar, NULL);
    free(messageStr);
    fclose(fp);
    fclose(outputFile);
} 

FILE* decryptDataDH(char* message, mpz_t key[]){

	return NULL;
} 

void decryptDataRSA(char* message, mpz_t key[]){
	FILE * fp;
    FILE *output;
	int len = 0;
    char *fName = "cipheredRSA.txt";

	fp = fopen(message, "r");
    output = fopen(fName, "w");
	//in case something goes wrong with files
	if (fp==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)
    fseek(fp, 0, SEEK_SET);

    mpz_t ciphChar, msgChar;
    unsigned int ciphInt;
    mpz_inits(ciphChar, msgChar, NULL);

    while (fscanf(fp, "%u", &ciphInt) != EOF)
    {
        mpz_set_ui(ciphChar, ciphInt);
        mpz_powm(msgChar, ciphChar, key[1], key[0]); // m = c^d mod n
        printf("Character read: %c \n", ciphInt);
        fprintf(output, "%u", (unsigned)mpz_get_ui(msgChar));
        fprintf(stdout, "%u\t", ciphInt);
    }
    printf("\n");
    mpz_clears(ciphChar, msgChar, NULL);
    fclose(fp);
    fclose(output);
} 