//
// FILENAME: factorial.hpp
//

#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

template<class T>
inline T factorial( unsigned int v )
{
    T f = 1;

    while ( v ) {
        f *= v;
        --v;
    }

    return f;
}

#endif // FACTORIAL_HPP
