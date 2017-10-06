//
// FILENAME: pollard_p_minus_one_factorization.hpp
//

#ifndef POLLARD_P_MINUS_ONE_FACTORIZATION_HPP
#define POLLARD_P_MINUS_ONE_FACTORIZATION_HPP

#include "gcd.hpp"
#include "discrete_exponent.hpp"
#include "factorial.hpp"

// Use Pollard's p - 1 method to find a non-trivial factor of a composite number

template<class T>
inline T pollard_p_minus_one_factorization( T const& composite, unsigned int bound )
{
    for ( unsigned int t = 1 ; t < bound ; ++t ) {

        // gcd( modpow( 2, t!, n ) - 1, n )
        const T factor = gcd( discrete_exponent<T>( 2, factorial<T>( t ), composite ) - 1, composite );

        // non-trivial factor
        if ( 1 < factor && factor < composite ) {
            return factor;
        }

        // trivial factor
        if ( factor == 1 ) {
            continue;
        }

        // trivial factor
        if ( factor == composite ) {
            continue;
        }

        throw "out of range";
    }

    throw "giving up";
}

#endif // POLLARD_P_MINUS_ONE_FACTORIZATION_HPP
