#include <limits>

#include "kdtree_constants.h"

namespace datastructures {

const std::size_t Constants::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX
    = std::numeric_limits< size_t >::max() - 1;

const std::size_t Constants::KDTREE_UNINITIALIZED_HYPERPLANE_VALUE
    = 0;

const std::size_t Constants::KDTREE_EMPTY_SET_VARIANCE
    = 0u;

const std::size_t Constants::KDTREE_EMPTY_SET_MEDIAN
    = 0u;

const std::string Constants::KDTREE_SIMPLE_VARIETY
    = "Simple KDTree Implementations";

const double Constants::KDTREE_INVALID_DISTANCE
    = -1.0L;

} // namespace datastructures
