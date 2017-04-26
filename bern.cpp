#include <iostream>
#include <type_traits>
#include <ratio>
using std::cout;
using std::endl;
using std::ratio;
using std::ratio_add;
using std::ratio_multiply;

template <size_t N, size_t K>
struct bin_coef {
    static const size_t val = (N - K + 1) * bin_coef<N, K - 1>::val / K;
};

template <size_t N>
struct bin_coef<N, 0> {
    static const size_t val = 1;
};

template <size_t N>
struct Bern;

template <size_t Hi, size_t Lo>
struct sum {
    static const Bern<Hi - Lo> cur;
    static const sum<Hi, Lo + 1> next; 
    static const ratio_add<
                    ratio_multiply<
                        ratio<-1 * bin_coef<Hi + 1, Lo + 1>::val, Hi + 1>,
                        ratio<cur.num, cur.den>>,
                    ratio<next.val.num, next.val.den>> tmp;
    static const ratio<tmp.num, tmp.den> val;
};

template <size_t Hi>
struct sum<Hi, Hi> {
    static const std::ratio<-1, Hi + 1> val;
};

template <size_t N>
struct Bern {
    static const sum<N, 1> res;
    static const std::intmax_t  num = res.val.num,
                                den = res.val.den;
};

template <>
struct Bern<0> {
    static const std::intmax_t  num = 1,
                                den = 1;
};

#define check(N) \
    cout << #N << " bernoulli " << Bern<N>::num << " / " << Bern<N>::den << endl << endl;

int main ()
{
    check(31)
    check(32)
    check(33)    
    check(34)
    check(35)    
    return 0;
}
