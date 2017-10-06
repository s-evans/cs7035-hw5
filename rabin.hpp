//
// FILENAME: rabin.hpp
//

#ifndef RABIN_H
#define RABIN_H

#include "discrete_exponent.hpp"

// Rabin’s Test
// The Rabin primality test takes a possible prime number n and a random number as input and returns true if n might be prime and returns false if n is composite.

inline bool rabin( mpz_class const& possible_prime, mpz_class const& random )
{
    int k = 0;

    mpz_class q = possible_prime - 1;

    while ( q % 2 == 0 ) {
        ++k;
        q = q / 2;
    }

    mpz_class result = discrete_exponential( random, q, possible_prime );

    if ( result == 1 ) {
        return true;
    }

    if ( result == q ) {
        return true;
    }

    do {
        result = ( result * result ) % possible_prime;

        if ( result == q ) {
            return true;
        }

        --k;
    } while ( result != 1 && k > 0 );

    return false;
}

#endif // RABIN_H
