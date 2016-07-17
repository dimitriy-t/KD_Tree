#ifndef KDTREE_CONSTANTS_H
#define KDTREE_CONSTANTS_H

#include <cstddef>
#include <string>

namespace datastructures {

struct Defaults {
    static const std::size_t KDTREE_UNINITIALIZED_HYPERPLANE_INDEX;
        // Used in default ctor to signify uninitialized value of
        // divisor hyperplane index

    static const std::size_t KDTREE_UNINITIALIZED_HYPERPLANE_VALUE;
        // Used in default ctor to signify uninitialized value of
        // divisor hyperplane position

    static const std::size_t KDTREE_EMPTY_SET_VARIANCE;
        // Defines a variance of an empty set

    static const std::size_t KDTREE_EMPTY_SET_MEDIAN;
        // Defines a median of an empty set

    static const std::string KDTREE_SIMPLE_VARIETY;
        // Denotes a plain vanilla KDTree implementations
};

} // namespace datastructures

#endif //KDTREE_CONSTANTS_H
