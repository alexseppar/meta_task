#include <iostream>
using std::cout;
using std::endl;

template <bool state, typename Ta, typename Tb>
struct ITE;

template <typename Ta, typename Tb>
struct ITE<true, Ta, Tb> {
    typedef Ta res;
};

template <typename Ta, typename Tb>
struct ITE<false, Ta, Tb> {
    typedef Tb res;
};

template <int N, int LO = 1, int HI = N>
struct Sqrt {
    enum { mid = (LO + HI + 1) / 2 }; 
    typedef typename ITE<(N < mid * mid), Sqrt<N, LO, mid - 1>, 
                                          Sqrt<N, mid, HI>     >::res RES;
    enum { res = RES::res };
};

template <int N, int S>
struct Sqrt <N, S, S> {
    enum { res = S };
};

template <typename T, T val>
struct constant {
    typedef T type;
    static const T value = val;
};

using true_type = constant<bool, true>;

using false_type = constant<bool, false>;

template <size_t N, size_t count, size_t check>
struct is_prime_helper {
    typedef typename ITE <N % count == 0, false_type, is_prime_helper<N, count + 1, check>>::res RES;
    static const bool value = RES::value;
};

template <size_t N, size_t count>
struct is_prime_helper<N, count, count> {
    static const bool value = true;
};

template <size_t N>
struct is_prime {
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
    enum { val = helper<N, count + 1, product + 2, is_prime<product + 2>::value>::val };
};

template <size_t N, size_t count, size_t product>
struct helper<N, count, product, false> {
    enum { val = helper<N, count, product + 2, is_prime<product + 2>::value>::val };
};

template <size_t N>
struct Nth_prime {
    enum { value = helper <N, 2, 3, true>::val };
};

template <>
struct Nth_prime<1> {
    enum { value = 2 };
};

#define check(num) \
    cout << #num << "th prime is " << Nth_prime<num>::value << endl;

int main ()
{
    check(100)
    return 0;
}
