#ifndef KDTREE_TYPES_H
#define KDTREE_TYPES_H

#include <vector>
#include <set>
#include <iostream>

namespace datastructures {

struct Types {

    template< typename T >
    using Point = std::vector< T >;

    template< typename T >
    using Points = std::vector< Point< T > >;

    template< typename T >
    using AxisMinMax = std::vector< std::pair< T, T > >;

};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs, const Types::Point< T >& rhs )
{
    std::cout << std::endl;

    lhs << "Point:[ "
        << "cardinality = '" << std::dec << rhs.size() << "'";

    if ( rhs.size() )
    {
        lhs << ", pos = (";

        for ( size_t i = 0; i < rhs.size() - 1; ++i )
        {
            lhs << "'" << std::dec << rhs[ i ] << "', ";
        }

        lhs << " '" << std::dec << rhs[ rhs.size() - 1 ] << "')";
    }

    lhs << " ]";

    return lhs;
}

template< typename T >
std::ostream& operator<<( std::ostream& lhs, const Types::Points< T >& rhs )
{
    std::cout << std::endl;

    lhs << "Points:[ "
    << "size = '" << std::dec << rhs.size() << "'";

    if ( rhs.size() )
    {
        lhs << ", ";

        for ( size_t i = 0; i < rhs.size() - 1; ++i )
        {
            lhs << rhs[ i ] << ", ";
        }

        lhs << rhs[ rhs.size() - 1 ];
    }

    lhs << " ]";

    return lhs;
}

} // namespace datastructures

#endif //KDTREE_TYPES_H
