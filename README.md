# Assignment 1: Project for system security course at TUC.
## RSA Algorithm & Diffie–Hellman Key Exchange
### Diffie-Hellman Key Exchange Tool
<p>The dh_assign_1.c file contains the implementation of the algorithm.
From the command line the program recieves the numbers p, g, a, b and it produces the shared key for Alice and Bob. Then it stores to the output file the results: a,b,share_key.
Every type of number variables are mpz_t from the GMP library and the arithmetic operations are also included from the GMP library.</p>
<p>In order to test the code you can try this example: ./dh_assign_1 -o output.txt -p 23 -g 9 -a 15 -b 2</p>
