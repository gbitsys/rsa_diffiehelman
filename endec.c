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

	//in case something goes wrong
	if (fp==NULL){
		printf("File error!!!\n");
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
    char tmp[len];
    mpz_inits(msgChar, ciphChar, NULL);

    do{
    	mpz_set_ui(msgChar, (unsigned int)messageStr[i]);
    	mpz_powm(ciphChar, msgChar, key[1], key[0]); //c = m^e mod n
    	tmp[i] = (char) mpz_get_ui(ciphChar);
    	fputc(tmp[i], outputFile);
    	i++;
    }while(i<len);

    printf("[DEBUG] ciphered text is: %s\n", tmp);
    //preventing memory leaks
    free(messageStr);
    fclose(fp);
    fclose(outputFile);
} 

FILE* decryptDataDH(char* message, mpz_t key[]){

	return NULL;
} 

FILE* decryptDataRSA(char* message, mpz_t key[]){
	return NULL;
} 