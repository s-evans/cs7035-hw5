//
// FILENAME: fibonacci_test.hpp
//

#ifndef FIBONACCI_TEST_H
#define FIBONACCI_TEST_H

#include "discrete_exponent.hpp"
#include "fibonacci_matrix.hpp"

// Returns the Fibonacci order offset for use in the Fibonacci test for a given prime
template<class Prime>
inline int get_prime_offset( Prime possible_prime )
{
    Prime tmp;

    possible_prime -= 1; // p-1
    tmp = possible_prime;
    tmp %= 5;
    if ( tmp == 0 ) { // 5 | (p - 1)
        return -1;
    }

    possible_prime -= 1; // p-2
    tmp = possible_prime;
    tmp %= 5;
    if ( tmp == 0 ) { // 5 | (p - 2)
        return 1;
    }

    possible_prime -= 1; // p-3
    tmp = possible_prime;
    tmp %= 5;
    if ( tmp == 0 ) { // 5 | (p - 3)
        return 1;
    }

    possible_prime -= 1; // p-4
    tmp = possible_prime;
    tmp %= 5;
    if ( tmp == 0 ) { // 5 | (p - 4)
        return -1;
    }

    return 0;
}

template<class Prime>
inline bool fibonacci_test( Prime possible_prime )
{
    const int offset = get_prime_offset( possible_prime );

    if ( offset == 0 ) {
        return false;
    }

    using fmt = fibonacci_matrix<Prime>;

    auto fmodp = discrete_exponent<typename fmt::type, Prime, Prime>(
        identity<fmt>::get(), possible_prime + offset, possible_prime, identity<fmt>::get() );

    if ( fmodp(1, 1) == 0 ) {
        return true;
    }

    return false;
}

#endif // FIBONACCI_TEST_H
