#ifndef KDTREE_CONSTANTS_H
#define KDTREE_CONSTANTS_H

#include <cstddef>
#include <string>

namespace datastructures {

struct Constants {
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

    static const double KDTREE_INVALID_DISTANCE;
        // Denotes an error output resulting from an attempt to
        // calculate distance between points of different
        // cardinality

    static const double KDTREE_MAX_DISTANCE;
        // Denotes an error output resulting from an attempt to
        // calculate distance between points of different
        // cardinality

    static const size_t KDTREE_ERROR_INDEX;
        // Denotes an error output resulting from an attempt to
        // search for a point either on an empty tree on in case of
        // cardinality mismatch

    static const std::string KDTREE_HYPERPLANE_MARKER;
        // Denotes an upcoming hyperplane node line in a serialized
        // file stream

    static const std::string KDTREE_LEAF_MARKER;
        // Denotes an upcoming leaf node line in a serialized
        // file stream
};

} // namespace datastructures

#endif //KDTREE_CONSTANTS_H
