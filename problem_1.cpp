//
// FILENAME: problem_1.cpp
//

#include <cstdlib>
#include <iostream>
#include <gmpxx.h>
#include <array>
#include <algorithm>
#include "gcd.hpp"
#include "inverse.hpp"

struct structured_pair {
    mpz_class coefficient;
    mpz_class offset;
};

int main()
{
    // Known outputs of pseudorandom generator
    std::array<mpz_class, 5> const X{
        56687054115473550533_mpz,
        71501923691929981066_mpz,
        1162551557687152936_mpz,
        88117163952857350660_mpz,
        16754986973331962115_mpz
    };

    // List the additional pseudorandom output value X[10]
    mpz_class const check = 66775494619620378439_mpz;

    // Get the lower bound of M to validate solution
    mpz_class const lower_bound_m = std::max( *std::max_element( X.cbegin(), X.cend() ), check ) + 1;

    // Get the B term on its own using the first equation
    structured_pair const b{ -X[2], X[3] };  // B = ( -X[i-1]*A + X[i] ) % M

    // Set up the three remaining equations
    structured_pair G[3] = { // X[i-1]*A - X[i] = 0
        {X[0], -X[1]},
        {X[1], -X[2]},
        {X[3], -X[4]}
    };

    // Substitute B into the three other equations
    for ( auto && g : G ) {
        g.coefficient += b.coefficient;
        g.offset += b.offset;
    }

    // Using one of the equations, cancel out the A term of the other two equations
    mpz_class m[2] = {
        { G[0].coefficient * G[1].offset - G[1].coefficient * G[0].offset },
        { G[0].coefficient * G[2].offset - G[2].coefficient * G[0].offset }
    };

    // Use gcd of two solutions to get M
    mpz_class const M = gcd<mpz_class>( m[0], m[1] );

    // Verify M
    if ( M < lower_bound_m ) {
        std::cout << "M is too low" << std::endl;
        std::cout << M << " < " << lower_bound_m << std::endl;
        return EXIT_FAILURE;
    }

    // Use M in previous equations to find A
    mpz_class const A = ( ( G[0].offset - M ) * -inverse( G[0].coefficient, M ) ) % M;

    // Use A and M in previous equations to find B
    mpz_class const B = ( ( -X[0] * A ) % M + X[1] % M ) % M;

    // Calculate all pseudorandom outputs
    std::array<mpz_class, 12> R = { X[0] };
    for ( size_t i = 1 ; i < R.size() ; ++i ) {
        R[i] = ( A * R[i - 1] % M + B % M ) % M;
    }

    // Check pseudorandom solutions against known outputs
    for ( size_t i = 1 ; i < X.size() ; ++i ) {
        if ( X[i] != R[i] ) {
            std::cout << "failed to verify solution for X[" << i << "]" << std::endl;
            std::cout << X[i] << " != " << R[i] << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Check X[10]
    if ( R[10] != check ) {
        std::cout << "failed to verify solution X[10]" << std::endl;
        std::cout << R[10] << " != " << check << std::endl;
        return EXIT_FAILURE;
    }

    // Print solutions
    std::cout << "Pseudorandom Values" << std::endl;
    for ( size_t i = 1 ; i < R.size() ; ++i ) {
        std::cout << " X[" << i << "] = " << R[i] << std::endl;
    }

    // Print values that were found
    std::cout << "Solution" << std::endl;
    std::cout << " A = " << A << std::endl;
    std::cout << " B = " << B << std::endl;
    std::cout << " M = " << M << std::endl;

    return EXIT_SUCCESS;
}
