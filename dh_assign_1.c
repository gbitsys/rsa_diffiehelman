#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <gmp.h>

typedef struct Person_keys{
    mpz_t secret_choice;
    mpz_t choice_sent;
    mpz_t result;
}Person;

int main(int argc, char* argv[])
{
    mpz_t p, g, a, b; //prime number p and base g, secret key a & b
    mpz_inits(p, g, a, b, NULL);
    char* output;
    FILE *fptr;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-p") == 0){
            mpz_set_si(p, atoi(argv[i+1]));
            gmp_printf("p is %Zd\n", p);
        }
        else if(strcmp(argv[i], "-g") == 0){
            mpz_set_si(g, atoi(argv[i+1]));
            gmp_printf("g is %Zd\n", g);
        }
        else if(strcmp(argv[i], "-a") == 0){
            mpz_set_si(a, atoi(argv[i+1]));
            gmp_printf("a is %Zd\n", a);
        }
        else if(strcmp(argv[i], "-b") == 0){
            mpz_set_si(b, atoi(argv[i+1]));
            gmp_printf("b is %Zd\n", b);
        }
        else if(strcmp(argv[i], "-o") == 0){
            output = argv[i+1];
        }
    }

    fptr = fopen(output, "w");

    Person *Alice = malloc(sizeof(Person));
    assert(Alice != NULL);
    person_secret_choice(Alice, a, g, p);

    gmp_printf("Alice has secret int %Zd and sent %Zd\n", Alice->secret_choice, Alice->choice_sent);

    Person *Bob = malloc(sizeof(Person));
    assert(Alice != NULL);
    person_secret_choice(Bob, b, g, p);

    gmp_printf("Bob has secret int %Zd and sent %Zd\n", Bob->secret_choice, Bob->choice_sent);

    person_compute_s(Alice, Bob, p);
    person_compute_s(Bob, Alice, p);

    gmp_printf("Alice and Bob share key is: %Zd\t%Zd\n", Alice->result, Bob->result);

    gmp_fprintf(fptr, "%Zd,%Zd,%Zd", Alice->choice_sent, Bob->choice_sent, Alice->result);

    free(Alice);
    free(Bob);
    fclose(fptr);
    mpz_clears(p, g, a, b, NULL);
    return 0;
}


void person_secret_choice(Person *person, mpz_t secret_int,  mpz_t g, mpz_t p){
    mpz_inits(person->secret_choice, person->choice_sent, NULL);
    mpz_set(person->secret_choice, secret_int);
    mpz_t temp;
    mpz_init(temp);
    mpz_pow_ui(temp, g, mpz_get_si(secret_int));
    mpz_mod(person->choice_sent, temp, p);
    mpz_clear(temp);
};

void person_compute_s(Person *current_person, Person *other_person, mpz_t p){
    mpz_init(current_person->result);
    mpz_t temp;
    mpz_init(temp);
    mpz_pow_ui(temp, other_person->choice_sent, mpz_get_si(current_person->secret_choice));
    mpz_mod(current_person->result, temp, p);
    mpz_clear(temp);
};

