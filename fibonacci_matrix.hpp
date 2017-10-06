//
// FILENAME: fibonacci_matrix.hpp
//

#ifndef FIBONACCI_MATRIX_H
#define FIBONACCI_MATRIX_H

#include "matrix.hpp"
#include "identity.hpp"

template<class T>
class fibonacci_matrix
{
public:

    using type = matrix<T, 2, 2>;

    // Create a Fibonacci matrix
    static inline constexpr type identity()
    {
        return type{ 1, 1, 1, 0 };
    }

    fibonacci_matrix() = delete;

};

template<class T> struct identity<fibonacci_matrix<T>> {
    using type = matrix<T, 2, 2>;
    static inline constexpr type get()
    {
        return fibonacci_matrix<T>::identity();
    }
};

#endif // FIBONACCI_MATRIX_H
