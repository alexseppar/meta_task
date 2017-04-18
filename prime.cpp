#include <stdlib.h>
#include "prime.h"
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
using namespace std;



inline int get_digit(int* arr, int i, int N)//returns digit which stays on "i" place
{
    assert(i <= N);
    assert(i >= 0);
    return arr[i];
}

inline int sum(int N)
{
    int Num = N * (N + 1) / 2;
    return Num;
}

inline int * create_arr_for_num(int N)
{
    int * arr = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
        arr[i] = (N - i) ;
    return arr;
}

inline int count_num(int *arr, int N)//returns max n-alldigit number
{
    int Num = 0;
    for(int i = 0; i < N; i++)
        Num+= arr[i] *((int) pow(10, N - i - 1));
    assert(Num <= INT_MAX);
    return Num;
}

inline int fact(int n)// just factorial
{
    int fact = 1;
    for(int i = 2; i <= n; i++)
        fact = fact * i;
    assert( fact <= INT_MAX);
    return fact;
}

inline void change_digits(int * arr, int j, int i)//changes digits on "n" and "i" places
{
    int c = arr[j];
    arr[j] = arr[i];
    arr[i] = c;
}

bool prime_check(int Num, int N)//checks if the Num is prime
{
    if(((Num - 1) /( (Num - 1)/6)) == 6 || ((Num + 1) / ((Num + 1)/6)) == 6)
    {
        if(!(Num%2) || !(sum(N)%3)) return false;
        else
        {
            int imax = (int)sqrt(Num);
            for(int i = 5; i <= imax; i+=2)
                    if(!(Num%i)) return false;
        }
        return true;
    }
    else
        return false;
}

inline void sort(int * arr, int i, int N)
{
    int replace = 1;
    while(replace)
    {
        replace = 0;
        for(int j =i + 1 ; j < N; j++)
        {
            if(get_digit(arr,j,N) < get_digit(arr,j+1, N))
            { 
                change_digits(arr, j, j+1); 
                replace = 1;
            }
        }
    }
}

int comb( int n)//makes needed numbers and returns max prime or "0" if such number was not found
{

for(int N = n; N > 2; N--)
    {
        int * arr = create_arr_for_num(N);
        int  count = 1,  check = fact(N), Num = count_num(arr,N);
        if(prime_check(Num, N)) return Num;
        int right, left, i = N - 1, j;
    while(count!=check)
    {
        do
        {
            right = get_digit(arr,i, N);
            left = get_digit(arr, i - 1, N);
            i--;
        }while(right > left);
        j = i ;
        i = N - 1;
        do
        {
            right = get_digit(arr,i, N);
            i--;
        }while(right > left);
        change_digits(arr,i + 1, j);
        count++;
        if(j < N - 2 )  sort(arr,j , N);
        Num = count_num(arr,N);
        if(prime_check(Num,N)) return Num;
        i = N - 1;
     }
     }
 return 0;
}

bool  is_prime (sieve_t * sieve, size_t i)
{
    assert(sieve->arr);
    assert(i < sieve->size);
    if (i == 2) return true;
    if (i % 2 == 0) return false;
    return !(sieve->arr[((i - 1)/2)/8] & 1<<(7 -(((i -1)/2)%8)));
}

unsigned long find_next_prime(sieve_t *sieve, unsigned long Num)
{
    assert(sieve);
    if (Num % 2 == 0)
        Num += 1;
    while (!is_prime(sieve, Num))
        Num += 2;
    return Num;
}

unsigned long find_prev_prime(sieve_t *sieve, unsigned long Num)
{
    assert(sieve);
    if (Num % 2 == 0)
        Num += 1;
    while (!is_prime(sieve, Num))
        Num -= 2;
    return Num;
}

void Sieve_Maker(sieve_t * sieve)
{
    for(size_t i = 9; i < sieve->size; i+=6)
        sieve->arr[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);  
    for(size_t j = 6; j < sieve->size; j+=6)
    {
        if(is_prime(sieve, j - 1))
            for(size_t i = (j - 1)*(j - 1); i < sieve->size; i+=2*(j - 1)) 
                sieve->arr[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);
        
        if(is_prime(sieve, j + 1))
            for(size_t i = (j + 1)*(j + 1); i < sieve->size; i+=2*(j + 1)) 
                sieve->arr[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);
    }
}



int prime_seeker(sieve_t * sieve, int count)
{
    int i = 6, count_2 = 2, Needed_prime;
    if(count == 1) return 2;
    if(count == 2) return 3;
    assert(sieve->arr);
    while(1)
    {
        if(is_prime(sieve, i - 1)) {count_2++; Needed_prime = i - 1;}
        if (count_2 == count) return Needed_prime;
        if(is_prime(sieve, i + 1)) {count_2++; Needed_prime = i + 1;}
        if (count_2 == count) return Needed_prime;
        i+=6;
    }
    return Needed_prime;
}

void create_sieve(sieve_t *sieve, size_t memory)
{
    assert(sieve);
    sieve->arr = (char*) calloc(memory/16, sizeof(char));
    if (!sieve->arr)
    {
        fprintf(stderr, "Bad alloc (in create_sieve)\n");
        exit(1);
    }
    sieve->size = memory;
}

bool dtor_sieve(sieve_t *sieve)
{
    if (!sieve)
        return false;
    if (!sieve->arr)
        return true;
    free(sieve->arr);
    sieve->arr = NULL;
    return true;
}


