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
    using Points = std::set< Point< T > >;

    template< typename T >
    using AxisMinMax = std::vector< std::pair< T, T > >;

};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs, const Types::Point< T >& rhs )
{
    lhs << "Point:[ "
        << "cardinality = '" << std::dec << rhs.size() << "'";

    if ( rhs.size() )
    {
        lhs << ", pos = ( ";

        typename Types::Point< T >::const_iterator it = rhs.cbegin();
        lhs << "'" << std::dec << ( *it ) << "'";
        ++it;
        for ( ; it != rhs.cend(); ++it )
        {
            lhs << ", '" << std::dec << ( *it ) << "'";
        }

        lhs << " ) ";
    }

    lhs << "]";

    return lhs;
}

template< typename T >
std::ostream& operator<<( std::ostream& lhs, const Types::Points< T >& rhs )
{
    lhs << "Points:[ "
    << "size = '" << std::dec << rhs.size() << "'";

    if ( rhs.size() )
    {

        for ( typename Types::Points< T >::const_iterator it = rhs.cbegin();
              it != rhs.cend(); ++it )
        {
            lhs << ", " << std::dec << ( *it );
        }
    }

    lhs << " ]";

    return lhs;
}

} // namespace datastructures

#endif //KDTREE_TYPES_H
