//
// FILENAME: is_safe_prime.hpp
//

#ifndef IS_SAFE_PRIME_HPP
#define IS_SAFE_PRIME_HPP

#include "fibonacci_test.hpp"
#include "thousand_primes_test.hpp"

template<class Prime>
inline bool is_safe_prime( Prime prime )
{
    prime -= 1;
    prime /= 2;
    return thousand_primes_test( prime ) && fibonacci_test( prime );
}

#endif // IS_SAFE_PRIME_HPP
