//
// FILENAME: crt.hpp
//

#ifndef CRT_HPP
#define CRT_HPP

#include "inverse.hpp"

// Chinese remainder theorem
// Returns x such that 0 < x < mn and x is congruent to a (mod m), and x is congruent to b (mod n).
// Must have gcd(m,n) = 1.

template<class T>
inline T crt( T const& a, T const& b, T const& m, T const& n )
{
    T i = inverse<T>( m, n );

    if ( i == 0 ) {
        return 0;
    }

    T u = a % m;

    if ( u < 0 ) {
        u += m;
    }

    T v = b % n;

    if ( v < 0 ) {
        v += n;
    }

    T x = u + m * ( v - u ) * i;
    T r = m * n;

    x %= r;

    if ( x < 0 ) {
        x += r;
    }

    return x;
}

#endif // CRT_HPP
