//
// FILENAME: problem_2.cpp
//

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <gmpxx.h>
#include "fermat_test.hpp"

int main()
{
    // 10^150
    mpz_class const lower_bound = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000_mpz;

    // Start at the lower bound
    // Add one because even numbers aren't prime
    mpz_class possible_prime = lower_bound + 1;

    // Create the corresponding prime number for safe prime testing
    mpz_class possible_safe_prime = lower_bound / 2;

    // Sample the steady clock before beginning the calculation
    auto const start_time = std::chrono::steady_clock::now();

    // Increment possible_prime by two because even numbers are not prime
    // Increment possible_safe_prime by one to maintain the / 2 constraint
    for ( ; true ; ++++possible_prime, ++possible_safe_prime ) {

        // Test possible_prime for primality
        if ( !fermat_test<mpz_class>( 2, possible_prime ) ) {
            continue;
        }

        // Test possible_safe_prime for primality
        if ( !fermat_test<mpz_class>( 2, possible_safe_prime ) ) {
            continue;
        }

        // Sample the steady clock immediately following the calculation
        auto const end_time = std::chrono::steady_clock::now();
        auto const duration = end_time - start_time;
        auto const duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>( duration );

        // Print the answer for k
        std::cout << "k = " << possible_prime - lower_bound << std::endl;

        // Print the time in milliseconds
        std::cout << "time = " << duration_ms.count() << " ms" << std::endl;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
