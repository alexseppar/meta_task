#include <iostream>
#include <type_traits>
#include <ratio>
#include "prime_meta.hpp"
#include <cassert>

using std::cout;
using std::endl;
using std::ratio;
using std::ratio_add;
using std::ratio_multiply;
using std::conditional;
using std::true_type;
using std::false_type;

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
    typedef typename Bern<Hi - Lo>::res cur;
    typedef typename sum<Hi, Lo + 1>::val next; 
    typedef ratio_add<
               ratio_multiply<
                   ratio<-1 * bin_coef<Hi + 1, Lo + 1>::val, Hi + 1>,
                   ratio<cur::num, cur::den>>,
               ratio<next::num, next::den>> tmp;
    typedef ratio<tmp::num, tmp::den> val;
};

template <size_t Hi>
struct sum<Hi, Hi> {
    typedef ratio<-1, Hi + 1> val;
};

template <size_t N>
struct Bern {
    typedef typename sum<N, 1>::val res_;
    typedef ratio<res_::num, res_::den> res;
                                
};

template <>
struct Bern<0> {
    typedef ratio<1, 1> res;
};

template <size_t N, size_t Hi = 1>
struct prime_sum {
    typedef typename prime_sum<N, Hi + 1>::val next;
    typedef typename conditional<(N % Hi == 0 && isprime<Hi + 1>::value),
                                  ratio_add<ratio<1, Hi + 1>, ratio<next::num, next::den>>,
                                  ratio<next::num, next::den>>::type val;
};

template <size_t N>
struct prime_sum<N, N> {
    typedef typename conditional<isprime<N + 1>::value,
                                 ratio<1, N + 1>,
                                 ratio<0, 1>>::type val;
};

template <size_t N, size_t K = 1>
struct check_N_Berns {
    typedef typename conditional<(K > 2 ) && (K % 2 == 1),
                        ratio<0, 1>,
                        typename prime_sum<K, 1>::val>::type cur_sum;
    typedef typename Bern<K>::res cur_bern;
    static constexpr bool result = conditional<ratio_add<cur_bern, cur_sum>::den == 1,
                                 true_type,
                                 false_type>::type::value;
    check_N_Berns<N, K + 1> next;
    void all_check () { assert (result); next.all_check (); }
};

template <size_t N>
struct check_N_Berns<N, N> {
    typedef typename conditional<(N > 2 ) && (N % 2 == 1),
                        ratio<0, 1>,
                        typename prime_sum<N, 1>::val>::type cur_sum;
    typedef typename Bern<N>::res cur_bern;
    static constexpr bool result = conditional<ratio_add<cur_bern, cur_sum>::den == 1,
                                 true_type,
                                 false_type>::type::value;
    void all_check () { assert (result); }
};

int main ()
{
    check_N_Berns<35> nums;
    nums.all_check ();
    return 0;
}
