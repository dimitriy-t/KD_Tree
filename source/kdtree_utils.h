#ifndef KDTREE_UTILS_H
#define KDTREE_UTILS_H

#include "kdtree_types.h"
#include "kdtree_constants.h"

// @Purpose
//
// This struct provides simple mathematical utility functions in a
// separate, easily verifiable package

namespace datastructures {

struct Utils {
    // PRIMARY INTERFACE
    template< typename T >
    static size_t highestVariance( const Types::Points< T >& points );
        // Given a set of equally dimensional points finds an
        // with highest variance

    template< typename T >
    static size_t medianInAxis( const Types::Points< T >& points,
                                const size_t axis );
        // Given a set of equally dimensional points and a specific
        // axis find a median value of all the points on that axis
};

//============================================================================
//                  PRIMARY INTERFACE
//============================================================================

template< typename T >
size_t
Utils::highestVariance( const Types::Points< T >& points )
{
    // Sanity
    if ( !points.size() )
    {
        return Defaults::KDTREE_EMPTY_SET_VARIANCE;
    }

    return 123u;
}

template< typename T >
size_t
Utils::medianInAxis( const Types::Points< T >& points, const size_t axis )
{
    // Sanity
    if ( !points.size() )
    {
        return Defaults::KDTREE_EMPTY_SET_VARIANCE;
    }

    return 456u;
}

} // namespace datastructures

#endif //KDTREE_UTILS_H
