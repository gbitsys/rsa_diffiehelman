#include"endec.h"

//insert a message (name of file), an encryption key [n, e] receive encrypted message (RSA)
//key[0] = n, key[1] = e, key[2]=d
void encryptDataRSA(char * input_file, char* output_file, mpz_t key[]){
	FILE * fp;
    FILE *output;
	int len = 0;
	char c;
	fp = fopen(input_file, "r");
    output = fopen(output_file, "w");
	//in case something goes wrong
	if (fp==NULL || output==NULL){
		printf("File error!!!\n");
		return;
	}
	
	fseek(fp, 0, SEEK_END); 
    len = ftell(fp); //length of file (bytes)
    fseek(fp, 0, SEEK_SET);
<<<<<<< HEAD
=======

    char *messageStr; //this variable used to read text from the file 
    messageStr = malloc(sizeof(char)*len);
>>>>>>> e52e3eb (minor changes to endec.c)
    mpz_t ciphChar, msgChar;
    mpz_inits(msgChar, ciphChar, NULL);
    int i = 0;
    while (i<len)
    {
        c = fgetc(fp);
<<<<<<< HEAD
        mpz_set_ui(msgChar, (unsigned int)c);
        mpz_powm(ciphChar, msgChar, key[1], key[0]); // m = c^e mod n
        gmp_fprintf(output, "%Zd", ciphChar);
        i++;
        if(i<len){
            fprintf(output, "\n");
        }

    }
=======
        messageStr[i++] = (char) c; //reading char one by one 
        mpz_set_ui(msgChar, (unsigned int)c);
        mpz_powm(ciphChar, msgChar, key[1], key[0]); // m = c^d mod n
        fprintf(output, "%u\n", (unsigned int)mpz_get_ui(ciphChar));

    }
    messageStr[i]='\0';
   
    printf("[DEBUG]message is: %s\n", messageStr);

    

>>>>>>> e52e3eb (minor changes to endec.c)
    //preventing memory leaks
    mpz_clears(msgChar, ciphChar, NULL);
    fclose(output);
    fclose(fp);

} 

void decryptDataRSA(char * input_file, char* output_file, mpz_t key[]){
	FILE * fp;
    FILE *output;
<<<<<<< HEAD
    int len = 0;
	fp = fopen(input_file, "r");
    output = fopen(output_file, "w");
=======
	int len = 0;
    char *fName = "cipheredRSA2.txt";
    char *outputName = "decipheredRSA2.txt";
    gmp_printf("[DEBUG] n=%Zd e=%Zd\n",key[0], key[1]);
	fp = fopen(fName, "r");
    output = fopen(outputName, "w");
>>>>>>> e52e3eb (minor changes to endec.c)
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
<<<<<<< HEAD
    while (!feof(fp))
    {
        mpz_inp_str(ciphChar, fp, 10);
=======
    int i=0;
    while ((fscanf(fp, "%u\n", &ciphInt)==1) && i<len-1)
    {
        
        mpz_set_ui(ciphChar, (unsigned int)ciphInt);
>>>>>>> e52e3eb (minor changes to endec.c)
        mpz_powm(msgChar, ciphChar, key[1], key[0]); // m = c^d mod n
        gmp_fprintf(output, "%c", (char)mpz_get_ui(msgChar));
    }
<<<<<<< HEAD
    //preventing memory leaks 
=======

    printf("\n");

>>>>>>> e52e3eb (minor changes to endec.c)
    mpz_clears(ciphChar, msgChar, NULL);
    fclose(fp);
    fclose(output);
} 
