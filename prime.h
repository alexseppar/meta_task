#ifndef PRIME_H
#define PRIME_H

#include <cstdlib>
#include <algorithm>

class sieve final {
    size_t size_;
    char *memory_;
    void make_sieve ();
    public:
    sieve (size_t memory) : size_(memory), memory_(new char[size_ / 16]())
    { make_sieve (); }
    ~sieve () { if (memory_) delete [] memory_; }
    sieve (const sieve& that) : size_(that.size_), memory_(new char[size_ / 16]())
    { 
        std::copy (that.memory_, that.memory_ + size_ / 16, memory_);
        make_sieve ();
    }
    sieve (sieve&& that) : size_(that.size_), memory_(that.memory_)
    { 
        that.memory_ = nullptr; that.size_ = 0;
    }
    bool operator== (const sieve& that) const
    {
        return (memory_ == that.memory_ && size_ == that.size_);
    }
    sieve& operator= (const sieve& that);
    sieve& operator= (sieve&& that); 
    bool is_prime (size_t num) const;
    size_t prime_seeker (size_t num) const;
};

#endif
