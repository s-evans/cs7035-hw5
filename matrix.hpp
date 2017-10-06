//
// FILENAME: matrix.hpp
//

#ifndef MATRIX_H
#define MATRIX_H

#include <utility>
#include <string>
#include <stdexcept>
#include <sstream>
#include "identity.hpp"

// Generic matrix type
template<class T, size_t N, size_t M>
class matrix
{

public:

    // Contained type
    using type = T;

    // Row extent
    enum { row_extent = N };

    // Column extent
    enum { col_extent = M };

    // Total extent
    enum { extent = N * M };

    // Is matrix square?
    enum { is_square = ( N == M ) };

    // Create an identity matrix
    static inline constexpr matrix identity()
    {
        static_assert(matrix::is_square, "identity is defined for square matrices only");

        matrix tmp{0,};

        for ( size_t i = 0 ; i < N ; ++i ) {
            tmp( i, i ) = 1;
        }

        return tmp;
    }

    // Constructor
    // Row major order
    template<class... Args> constexpr inline
    matrix( Args&& ... args )
        : v_{ std::forward<Args>( args )... }
    {
    }

    // Default construct
    matrix() = default;

    // Destroy
    ~matrix() = default;

    // Copy
    matrix( matrix const& ) = default;

    // Assign
    matrix& operator=( matrix const& ) = default;

    // Move construct
    matrix( matrix&& ) = default;

    // Move assign
    matrix& operator=( matrix&& ) = default;

    // Access element
    inline constexpr type const& operator()( size_t row, size_t col ) const
    {
        return v_[get_idx( row, col )];
    }

    // Access element
    inline constexpr type& operator()( size_t row, size_t col )
    {
        return v_[get_idx( row, col )];
    }

    // Scalar multiplication
    template<class S> inline constexpr matrix& operator*=( S const& rhs )
    {
        for ( size_t i = 0 ; i < extent ; ++i ) {
            v_[i] *= rhs;
        }

        return *this;
    }

    // Scalar modular division
    template<class S> inline constexpr matrix& operator%=( S const& rhs )
    {
        for ( size_t i = 0 ; i < extent ; ++i ) {
            v_[i] %= rhs;
        }

        return *this;
    }

    // Square matrix multiplication
    inline matrix& operator*=( matrix const& rhs )
    {
        static_assert( is_square, "matrices must both be square" );

        matrix tmp;

        for ( size_t j = 0 ; j < N ; ++j ) {
            for ( size_t i = 0 ; i < N ; ++i ) {

                tmp( i, j ) = 0;

                for ( size_t k = 0 ; k < N ; ++k ) {
                    tmp( i, j ) += operator()( i, k ) * rhs( k, j );
                }
            }
        }

        *this = tmp;

        return *this;
    }

    // Convert matrix to a string
    std::string to_string() const
    {
        std::ostringstream oss;

        for ( size_t j = 0 ; j < col_extent ; ++j ) {

            oss << "[";

            for ( size_t i = 0 ; i < row_extent ; ++i ) {

                oss << operator()( i, j );

                if ( i != col_extent - 1 ) {
                    oss << " ";
                }
            }

            oss << "]" << std::endl;
        }

        return oss.str();
    }

    // Output matrix to a stream
    friend std::ostream& operator<<( std::ostream& os, matrix const& rhs )
    {
        return os << rhs.to_string();
    }

private:

    // Matrix data contents
    type v_[extent];

    // Compute index
    // Row major order
    static constexpr inline size_t get_idx( size_t row, size_t col )
    {
        return ( ( col >= col_extent ) ? throw std::out_of_range( "invalid column" ) :
                 ( ( row >= row_extent ) ? throw std::out_of_range( "invalid row" ) : ( row + col * col_extent ) ) );
    }

};

// Matrix multiplication
template<class T, size_t N, size_t M, size_t P> inline constexpr matrix<T, N, P> operator*( matrix<T, N, M> const& lhs, matrix<T, M, P> const& rhs )
{
    matrix<T, N, P> tmp{0,};

    for ( size_t j = 0 ; j < P ; ++j ) {
        for ( size_t i = 0 ; i < N ; ++i ) {
            for ( size_t k = 0 ; k < M ; ++k ) {
                tmp( i, j ) += lhs( i, k ) * rhs( k, j );
            }
        }
    }

    return tmp;
}

// Scalar modular division
template<class S, class T, size_t N, size_t M> inline constexpr matrix<T, N, M> operator%( matrix<T, N, M> const& lhs, S const& rhs )
{
    matrix<T, N, M> tmp = lhs;

    for ( size_t j = 0 ; j < M ; ++j ) {
        for ( size_t i = 0 ; i < N ; ++i ) {
            tmp( i, j ) %= rhs;
        }
    }

    return tmp;
}

template<class T, size_t N, size_t M> struct identity<matrix<T, N, M>> {
    static inline constexpr matrix<T, N, M> get() {
        return matrix<T, N, M>::identity();
    }
};

#endif // MATRIX_H
