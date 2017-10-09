//
// FILENAME: inverse.hpp
//

#ifndef INVERSE_HPP
#define INVERSE_HPP

// If gcd(a,b) = 1 it returns a-1,  0 < a-1 < b, such that a-1a = 1 (mod b)

template<class T>
inline T inverse( T a, T b )
{
    if ( b < 0 ) {
        b = -b;
    }

    a %= b;

    if ( a < 0 ) {
        a += b;
    }

    //initialize
    T u1 = 1;
    T u2 = 0;
    T u3 = a % b;
    T v1 = 0;
    T v2 = 1;
    T v3 = b;

    //if u is too big, reduce it mod v
    u3 %= v3;

    while ( v3 != 0 ) {
        T const q = u3 / v3;
        T const t1 = u1 - v1 * q;
        T const t2 = u2 - v2 * q;
        T const t3 = u3 - v3 * q;
        u1 = v1;
        u2 = v2;
        u3 = v3;
        v1 = t1;
        v2 = t2;
        v3 = t3;
    }

    u1 %= b;

    if ( u1 < 0 ) {
        u1 += b;
    }

    return u1;
}

#endif // INVERSE_HPP
