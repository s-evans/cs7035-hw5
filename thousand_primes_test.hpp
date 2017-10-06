//
// FILENAME: thousand_primes_test.hpp
//

#ifndef THOUSAND_PRIMES_TEST_H
#define THOUSAND_PRIMES_TEST_H

#include <array>
#include <algorithm>
#include "small_primes.hpp"

template<class T>
inline bool thousand_primes_test( T const& possible_prime )
{
    return std::none_of( small_primes.begin(), small_primes.end(), [&]( T const& q ) { return ( possible_prime % q == 0 ); } );
}

#endif // THOUSAND_PRIMES_TEST_H
