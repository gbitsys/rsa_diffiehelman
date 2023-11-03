#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int main(int argc, char * argv[]){

	mpz_t key_len;
	mpz_init(key_len); 
	char* input_file, output_file, key_file, func;

	for(int i=0; i<argc; i++){
		if(strcmp(argv[i], "-i") == 0){
            input_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-o") == 0){
            output_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-k") == 0){
            key_file = argv[i+1];   
        }
        else if(strcmp(argv[i], "-g") == 0){
            mpz_set_ui(key_len, atoi(argv[i+1]));
            generateRSAKeyPair(key_len);
        }
        else if(strcmp(argv[i], "-e") == 0){
            func = argv[i+1];
        }
        else if(strcmp(argv[i], "-d") == 0){
            func = argv[i+1];
        }
        else if(strcmp(argv[i], "-a") == 0){
            func = argv[i+1];
        }
	}

	if(func!=NULL && strcmp(func, "-e") == 0){
		printf("hello peos\n");
		encrypt(input_file, output_file, key_file);
	}

	mpz_clear(key_len);
	return 0;
}

void encrypt(char* input, char* output, char* keyf){
	FILE *fp;
    fp = fopen(keyf, "r");
    mpz_t keys[2];
    mpz_inits(keys[0], keys[1], NULL);

	mpz_inp_str(keys[0], fp, 10);
	mpz_inp_str(keys[1], fp, 10);

	encryptDataRSA(input, output, keys);

	mpz_clears(keys[0], keys[1], NULL);
	fclose(fp);
}

void generateRSAKeyPair(mpz_t given_len){
	mpz_t real_len, temp;
	mpz_inits(real_len, temp, NULL);
	mpz_set_ui(temp, 2);
	mpz_cdiv_q(real_len, given_len, temp); //real_len = len / 2
	mpz_clear(temp);

	mpz_t key[3];
	mpz_inits(key[0], key[1], key[2], NULL);
	randomPair(real_len, key);

	printf("jello\n");

	char* len_str = mpz_get_str(NULL, 10, given_len);
    char* public = (char*)malloc(strlen("public_") + strlen(len_str) + strlen(".key") + 1);
    char* private = (char*)malloc(strlen("private_") + strlen(len_str) + strlen(".key") + 1);
    
    // Copy the components into the result string
    strcpy(public, "public_");
    strcat(public, len_str);
    strcat(public, ".key");

    strcpy(private, "private_");
    strcat(private, len_str);
    strcat(private, ".key");
    
    FILE *public_file;
    FILE *private_file;
    public_file = fopen(public, "w");
    private_file = fopen(private, "w");

    randomPair(real_len, key);
    gmp_fprintf(public_file, "%Zd\n", key[0]);
    gmp_fprintf(public_file, "%Zd", key[2]);	//write n, d
    gmp_fprintf(private_file, "%Zd\n", key[0]);
    gmp_fprintf(private_file, "%Zd", key[1]);	//write n, e

    free(len_str);
    free(public);
    free(private);
    fclose(public_file);
    fclose(private_file);

	mpz_clears(key[0], key[1], key[2], real_len, NULL);
};
