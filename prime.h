#ifndef PRIME_H
#define PRIME_H

typedef struct sieve_t { char * arr; size_t size;} sieve_t;
const int   Test_Subjects[12] = {2, 3, 5, 7, 11, 13 , 17, 19, 23, 29, 31, 37};
const int   NUM_OF_SUBJECTS = 12;

bool            prime_check     (int Num, int N);
bool            is_prime        (sieve_t * sieve, size_t i);
void            Sieve_Maker     (sieve_t * sieve);
int             prime_seeker    (sieve_t * sieve, int count);
void            create_sieve    (sieve_t * sieve, size_t memory);
unsigned long   find_prev_prime (sieve_t *sieve, unsigned long Num);
unsigned long   find_next_prime (sieve_t *sieve, unsigned long Num);
bool            dtor_sieve      (sieve_t *sieve);
#endif
