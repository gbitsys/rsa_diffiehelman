#Project for system security course at TUC.
## RSA Algorithm & Diffie–Hellman Key Exchange
### Diffie-Hellman Key Exchange Tool
<p>The dh_assign_1.c file contains the implementation of the algorithm.
From the command line the program recieves the numbers p, g, a, b and it produces the shared key for Alice and Bob. Then it stores to the output file the results: a,b,share_key.
Every type of number variables are mpz_t from the GMP library and the arithmetic operations are also included from the GMP library.</p>
<p>In order to test the code you can try this example: ./dh_assign_1 -o output.txt -p 23 -g 9 -a 15 -b 2</p>

### RSA Different key length Tool
<p>This tool consists of 3 header files: endec.h, keygen.h, rsa_assign_1.h .</p>
 <ul>
  <li>endec.c : Contains the functions that ENCRYPT and DECRYPT a message</li>
  <li>keygen.c : Performs key generation for the RSA algorithm. The private keys are created [n, e] and the public keys too [n, d]</li>
  <li>rsa_assign_1.c : Contains the main function that reads the flags and functions accordingly</li>
</ul> 
<p>NOTE! For the -a flag case the program reads the file 'message.txt' and sores the results into the 'performance.txt' file.
You can try the test: ./rsa_assign_1 -a performance.txt</p>

For this project usage of GNU Multiple Precision Library was necessary because of dealing with very long numbers.
