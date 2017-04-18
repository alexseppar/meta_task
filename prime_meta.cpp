#include <iostream>
#include <type_traits>
#include <cassert>
#include "prime.h"

using std::cout;
using std::endl;
using std::conditional;
using std::false_type;
using std::true_type;

template <int N, int LO = 1, int HI = N>
struct Sqrt {
    enum { mid = (LO + HI + 1) / 2 }; 
    typedef typename conditional<(N < mid * mid), Sqrt<N, LO, mid - 1>, 
                                          Sqrt<N, mid, HI>     >::type RES;
    enum { res = RES::res };
};

template <int N, int S>
struct Sqrt <N, S, S> {
    enum { res = S };
};

template <size_t N, size_t count, size_t check>
struct is_prime_helper {
    typedef typename conditional <N % count == 0, false_type, is_prime_helper<N, count + 1, check>>::type RES;
    static const bool value = RES::value;
};

template <size_t N, size_t count>
struct is_prime_helper<N, count, count> {
    static const bool value = true;
};

template <size_t N>
struct isprime {
    static const bool value = is_prime_helper<N, 2, Sqrt<N>::res + 1>::value;
};

template <size_t N, size_t count, size_t product, bool prime>
struct helper;

template <size_t N, size_t product>
struct helper<N, N, product, true> {
    enum { val = product };
};

template <size_t N, size_t count, size_t product>
struct helper<N, count, product, true> {
    enum { val = helper<N, count + 1, product + 2, isprime<product + 2>::value>::val };
};

template <size_t N, size_t count, size_t product>
struct helper<N, count, product, false> {
    enum { val = helper<N, count, product + 2, isprime<product + 2>::value>::val };
};

template <size_t N>
struct Nth_prime {
    enum { value = helper <N, 2, 3, true>::val };
};

template <>
struct Nth_prime<1> {
    enum { value = 2 };
};

template <size_t N, size_t Last>
struct holder {
    static const size_t value = Nth_prime<N>::value;
    holder<N + 1, Last> next;
};

template <size_t N>
struct holder<N, N> {
    static const size_t value = Nth_prime<N>::value;
};

template <size_t N>
struct N_prime_nums {
    static holder<1, N> next;
};

template <size_t N, size_t K>
size_t
get (size_t n, holder<N, K> arg)
{
    if (n == 1)
    {
        return arg.value;
    }
    else
    {
        return get (n - 1, arg.next);
    }
}

template <size_t T>
size_t
get (size_t N, holder<T, T> arg)
{
    return arg.value;
}

int main ()
{
    auto nums = N_prime_nums<100>::next;
    sieve_t sieve;
    create_sieve (&sieve, 1300);
    Sieve_Maker (&sieve);    
    for (int i = 1; i <= 100; ++i)
    {
        assert (get (i, nums) == prime_seeker (&sieve, i));
    }
    return 0;
}
