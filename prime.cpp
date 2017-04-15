#include <iostream>
using std::cout;
using std::endl;

template <bool state, bool Ta, bool Tb>
struct ITE;

template <bool Ta, bool Tb>
struct ITE<true, Ta, Tb> {
    static const bool value = Ta;
};

template <bool Ta, bool Tb>
struct ITE<false, Ta, Tb> {
    static const bool value = Tb;
};

template <size_t N, size_t count>
struct is_prime_helper {
    static const bool value = ITE <N % count == 0, false, is_prime_helper<N, count + 1>::value>::value;
};

template <size_t N>
struct is_prime_helper<N, N> {
    static const bool value = true;
};

template <size_t N>
struct is_prime {
    static const bool value = is_prime_helper<N, 2>::value;
};

template <size_t N, size_t count, size_t product, bool prime>
struct helper;

template <size_t N, size_t product>
struct helper<N, N, product, true> {
    enum { val = product };
};

template <size_t N, size_t count, size_t product>
struct helper<N, count, product, true> {
    enum { val = helper<N, count + 1, product + 1, is_prime<product + 1>::value>::val };
};

template <size_t N, size_t count, size_t product>
struct helper<N, count, product, false> {
    enum { val = helper<N, count, product + 1, is_prime<product + 1>::value>::val };
};

template <size_t N>
struct Nth_prime {
    enum { value = helper <N, 1, 2, true>::val };
};

#define check(num) \
    cout << #num << "th prime is " << Nth_prime<num>::value << endl;

int main ()
{
    check(1)
    check(2)
    check(3)
    check(4)
    check(5)
    check(6)
    check(7)
    check(8)
    check(9)
    check(10)
    check(11)
    return 0;
}
