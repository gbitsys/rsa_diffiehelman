#include"rsa_assign_1.h"
#include "endec.h"
#include "keygen.h"
#include<time.h>
#define DEFAULTLEN 256

int main(int argc, char * argv[]){

	mpz_t keyLength;
	mpz_init(keyLength); 
	char* inputFile, *outputFile, *keyFile, *func;
    mpz_set_si(keyLength, DEFAULTLEN);

    //handling flags from cli
	for(int i=0; i<argc; i++){
		if(strcmp(argv[i], "-i") == 0){
            if (argv[i+1]!=NULL){
                inputFile = argv[i+1];
                printf("Input file: %s\n", inputFile);
                continue;
            }
            printf("Give arguments in right order\n");

        }
        else if(strcmp(argv[i], "-o") == 0){
            if (argv[i+1]!=NULL){
                outputFile = argv[i+1];
                printf("Output file: %s\n", outputFile);
                continue;
            }
            printf("Give arguments in right order\n");
        }
        else if(strcmp(argv[i], "-k") == 0){
            if (argv[i+1]!=NULL){
                keyFile = argv[i+1];
                continue; 
            } 
            printf("Give arguments in right order\n"); 
        }
        else if(strcmp(argv[i], "-g") == 0){
            if (argv[i+1]!=NULL){
                mpz_set_ui(keyLength, atoi(argv[i+1]));
                generateRSAKeyPair(keyLength);
                continue;
            }
            printf("Give arguments in right order\n");
        }
        else if(strcmp(argv[i], "-e") == 0){
            if (outputFile!=NULL && inputFile!=NULL && keyFile!=NULL){ //required -i -o -k
                func = "encrypt";
                continue;
            }
            printf("Give arguments in right order\n");
        }
        else if(strcmp(argv[i], "-d") == 0){
            if (outputFile!=NULL && inputFile!=NULL && keyFile!=NULL){ //required -i -o -k
                func = "decrypt";
                continue;
            }
            printf("Give arguments in right order\n");
        }
        else if(strcmp(argv[i], "-a") == 0){
            func = "all";
            continue;
        }
	}

   //passing flags to according functions
	if(func!=NULL && strcmp(func, "encrypt") == 0){
		printf("Encrypting ...\n");
		encrypt(inputFile, outputFile, keyFile);
	}
    if(func!=NULL && strcmp(func, "decrypt") == 0){
		printf("Decrypting ...\n");
		decrypt(inputFile, outputFile, keyFile);
	}
    if(func!=NULL && strcmp(func, "all") == 0){
        printf("Check file 'performance.txt' for statistics\n");
		performance("message.txt","pCipher.txt", "pDecipher");
	}
    

	mpz_clear(keyLength);
	return 0;
}

void encrypt(char* input, char* output, char* keyf){
    mpz_t keys[2];
    keyFile(keyf, keys);

	encryptDataRSA(input, output, keys);

	mpz_clears(keys[0], keys[1], NULL);
}

void decrypt(char* input, char* output, char* keyf){
    mpz_t keys[2];
    keyFile(keyf, keys);
	decryptDataRSA(input, output, keys);

	mpz_clears(keys[0], keys[1], NULL);
} 

//generate RSA key pair to specific files
void generateRSAKeyPair(mpz_t given_len){
	mpz_t real_len, temp;
	mpz_inits(real_len, temp, NULL);
	mpz_set_ui(temp, 2);
	mpz_cdiv_q(real_len, given_len, temp); //real_len = len / 2
	mpz_clear(temp);

	mpz_t key[3];
	mpz_inits(key[0], key[1], key[2], NULL);
	randomPair(real_len, key);

	printf("Generating key...\n");

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

//actions for -a flag (measurements in performance for each bit length key)
void performance(char *input, char *cipherTxt, char *decipherTxt){
    FILE * fp;
    fp = fopen("performance.txt", "w");
    if(fp==NULL) return;//checking for file error

    clock_t start, end;
    double cpu_time_used;
    mpz_t keyLength;
    mpz_t keys[2];
    mpz_inits(keyLength, keys[0], keys[1],NULL);

    //1024 bits
    start = clock();
    mpz_set_si(keyLength, 1024);
    generateRSAKeyPair(keyLength);
    end = clock()-start;
    fprintf(fp, "1024 bit key length generation: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("private_1024.key", keys);
    encryptDataRSA(input, cipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "1024 bit key length encryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("public_1024.key", keys);
    decryptDataRSA(cipherTxt, decipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "1024 bit key length decryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    fprintf(fp, "\n");

    //2048 bits
    start = clock();
    mpz_set_si(keyLength, 2048);
    generateRSAKeyPair(keyLength);
    end = clock()-start;
    fprintf(fp, "2048 bit key length generation: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("private_2048.key", keys);
    encryptDataRSA(input, cipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "2048 bit key length encryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("public_2048.key", keys);
    decryptDataRSA(cipherTxt, decipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "2048 bit key length decryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    fprintf(fp, "\n");

    //4096 bits
    start = clock();
    mpz_set_si(keyLength, 4096);
    generateRSAKeyPair(keyLength);
    end = clock()-start;
    fprintf(fp, "4096 bit key length generation: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("private_4096.key", keys);
    encryptDataRSA(input, cipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "4096 bit key length encryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);

    start = clock();
    keyFile("public_4096.key", keys);
    decryptDataRSA(cipherTxt, decipherTxt, keys);
    end = clock() - start;
    fprintf(fp, "4096 bit key length decryption: %f seconds\n", (double)end/CLOCKS_PER_SEC);
}

//reads key pair from file stores them into keys array
void keyFile(char *fileName, mpz_t keys[]){
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp==NULL)
        return;
    mpz_inits(keys[0], keys[1], NULL);

	mpz_inp_str(keys[0], fp, 10);
	mpz_inp_str(keys[1], fp, 10);
    fclose(fp);
}
