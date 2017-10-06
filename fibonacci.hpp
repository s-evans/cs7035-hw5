//
// FILENAME: fibonacci.hpp
//

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "gmpxx.h"
#include <vector>

/**
 * @brief Fibonacci function that uses iteration and dynamic programming
 *
 * @param order which fibonacci number to get
 *
 * @return fibonacci number
 */
inline mpz_class fibonacci( mpz_class const& order )
{
    if ( order < 0 ) {
        return -1;
    }

    static std::vector<mpz_class> cache{{mpz_class{0}, mpz_class{1}}};

    if ( order > cache.capacity() ) {
        cache.reserve( order.get_ui() );
    }

    for ( size_t end = cache.size() ; end <= order ; ++end ) {
        cache.emplace_back( cache[end - 2] + cache[end - 1] );
    }

    return cache[order.get_ui()];
}

#endif // FIBONACCI_H
