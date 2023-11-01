#include"keygen.h"
#include"endec.h"

int main(int argc, char * args[]){
	
		mpz_t key[2];
		mpz_inits(key[0], key[1], NULL);
		mpz_set_si(key[0], 33);
		mpz_set_si(key[1], 7);
	for(int i=0; i<argc; i++){
		printf("[DEBUG] No:%d arg:%s\n", i, args[i]);
		encryptDataRSA("message.txt", key);
		/*switch(){
			case "-i":

			case "-o":

			case "-k":

			case "-g":

			case "-d":

			case "-e":

			case "-a":

			case "-h":

			break;
		}*/
	}

	return 0;
}