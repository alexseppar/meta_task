#include "prime.h"
#include <cstdlib>
#include <cstdio>
#include <cassert>

sieve& sieve::operator= (const sieve& that)
{
    if (*this == that)
        return *this;
    delete [] memory_;
    size_ = that.size_;
    memory_ = new char[size_ / 16]();
    std::copy (that.memory_, that.memory_ + size_ / 16, memory_);
    return *this;
}

sieve& sieve::operator= (sieve&& that)
{
    if (*this == that)
        return *this;
    delete [] memory_;
    size_ = that.size_;
    memory_ = that.memory_;
    that.memory_ = nullptr;
    that.size_ = 0;
    return *this;
}

bool  sieve::is_prime (size_t i) const
{
    assert(memory_ != nullptr);
    assert(i < size_);
    if (i == 2) return true;
    if (i % 2 == 0) return false;
    return !(memory_[((i - 1)/2)/8] & 1<<(7 -(((i -1)/2)%8)));
}

void sieve::make_sieve()
{
    for(size_t i = 9; i < size_; i+=6)
        memory_[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);  
    for(size_t j = 6; j < size_; j+=6)
    {
        if(is_prime (j - 1))
            for(size_t i = (j - 1)*(j - 1); i < size_; i+=2*(j - 1)) 
                memory_[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);
        
        if(is_prime (j + 1))
            for(size_t i = (j + 1)*(j + 1); i < size_; i+=2*(j + 1)) 
                memory_[((i-1)/2)/8] |= 1<<(7 - ((i-1)/2)%8);
    }
}

size_t sieve::prime_seeker(size_t count) const
{
    int i = 6, count_2 = 2, Needed_prime;
    if(count == 1) return 2;
    if(count == 2) return 3;
    assert(memory_ != nullptr);
    while(1)
    {
        if(is_prime (i - 1)) {count_2++; Needed_prime = i - 1;}
        if (count_2 == count) return Needed_prime;
        if(is_prime (i + 1)) {count_2++; Needed_prime = i + 1;}
        if (count_2 == count) return Needed_prime;
        i+=6;
    }
    return Needed_prime;
}
