#include <limits>

#include "kdtree_constants.h"

namespace datastructures {

const std::size_t Defaults::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX
    = std::numeric_limits< size_t >::max() - 1;

const std::size_t Defaults::KDTREE_UNINITIALIZED_HYPERPLANE_VALUE
    = 0;

const std::size_t Defaults::KDTREE_EMPTY_SET_VARIANCE
    = 0u;

const std::size_t Defaults::KDTREE_EMPTY_SET_MEDIAN
    = 0u;
} // namespace datastructures
