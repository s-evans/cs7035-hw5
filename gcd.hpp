//
// FILENAME: gcd.hpp
//

#ifndef GCD_HPP
#define GCD_HPP

#include <utility>

// Returns greatest common divisor

template<class T>
inline T gcd( T a, T b )
{
    while ( b != 0 ) {
        const T t = b;
        b = a % b;
        a = t;
    }

    return a;
}

// Returns greatest common divisor
// Template full specialization for mpz_class types, using gmp specific gcd function

template<>
inline mpz_class gcd<mpz_class>( mpz_class a, mpz_class b )
{
    mpz_class out;
    mpz_gcd( out.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t() );
    return std::move( out );
}

#endif // GCD_HPP
