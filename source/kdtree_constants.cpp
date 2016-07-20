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
    = "Simple KDTree Implementation";

const double Constants::KDTREE_INVALID_DISTANCE
    = -1.0L;

const double Constants::KDTREE_MAX_DISTANCE
    = std::numeric_limits< double >::max();

const size_t Constants::KDTREE_ERROR_INDEX
    = std::numeric_limits< size_t >::max() - 2;

const std::string Constants::KDTREE_HYPERPLANE_MARKER
    = "HYPERPLANE";

const std::string Constants::KDTREE_LEAF_MARKER
    = "LEAF";

const std::string Constants::KDTREE_EMPTY_MARKER
    = "EMPTY TREE";

const std::string Constants::KDTREE_NON_EMPTY_MARKER
    = "NON EMPTY TREE";

} // namespace datastructures
