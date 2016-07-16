#ifndef KDTREE_TYPES_H
#define KDTREE_TYPES_H

#include <vector>
#include <set>

namespace datastructures {

struct Types {

    template< typename T >
    using Point = std::vector< T >;

    template< typename T >
    using Points = std::vector< Point< T > >;

    template< typename T >
    using AxisMinMax = std::vector< std::pair< T, T > >;

};

} // namespace datastructures

#endif //KDTREE_TYPES_H
