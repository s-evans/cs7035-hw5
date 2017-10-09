#ifndef LCM_HPP
#define LCM_HPP

#include "gcd.hpp"

// Returns least common multiple

template<class T>
inline T lcm( T const& a, T const& b )
{
    return ( a * b ) / gcd<T>( a, b );
}

#endif // LCM_HPP
