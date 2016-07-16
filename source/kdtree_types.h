#ifndef KDTREE_TYPES_H
#define KDTREE_TYPES_H

#include <vector>
#include <set>

namespace datastructures {

struct Types {

    template< typename T >
    using Point = std::vector< T >;

    template< typename T >
    using Points = std::set< Point< T > >;

};

} // namespace datastructures

#endif //KDTREE_TYPES_H
