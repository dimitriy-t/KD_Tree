#ifndef KDTREE_H
#define KDTREE_H

#include <memory>

#include "kdtree_types.h"
#include "kdtree_node.h"
#include "kdtree_hyperplane.h"
#include "kdtree_utils.h"
#include "kdtree_constants.h"

// @Purpose
//
// This is base class for a simple KDTree datastructure implementation

namespace datastructures {

template< typename T >
class KDTree {
public:

    KDTree();
        // default ctor

    KDTree( const KDTree< T >& other );
        // Copy constructor, copies the pointer contained in other, not the
        // bisection
        // Calls build() helper

    KDTree( const Types::Points< T >& points );
        // Constructor, throws in case points are of different length
        // Calls build() helper

    ~KDTree();
        // default dtor

    // OPERATORS
    KDTree& operator=( const KDTree< T >& other );
        // Assignment operator. Calls copy; do this in child classes
        // when overloaded.
        // Note that this operator will copy the the points contained within
        // the provided tree, yet will build its own bisecting structure of the
        // space using own chooseBestSplit() implementation
        // Calls build() helper

    bool operator==( const KDTree< T >& other ) const;
        // Equality. Calls equals, do this in child classes
        // when overloaded.
        // Calls build() helper

    bool operator!=( const KDTree< T >& other ) const;
        // Non-equality.  Calls equals, do this in child classes
        // when overloaded.

    // PRIMARY INTERFACE
    bool serialize( const std::string& filename ) const;
        // Writes the tree to the provided file location.
        // Returns true on success and false otherwise.

    bool deserialize( const std::string& filename );
        // Loads the contents of the data via the contents of the file
        // Returns true on success and false otherwise.

    const Types::Point< T > nearestPoint(
            const Types::Point< T >& pointOfInterest ) const;
        // Returns const ref the closes point in a tree to the point of interest.
        // In case the tree is empty or there is a cardinality mismatch -
        // empty point is returned
        // Calls nearestPointIndexHelper()

    size_t nearestPointIndex( const Types::Point< T >& pointOfInterest ) const;
        // Returns index closes point in a tree to the point of interest.
        // In case the tree is empty or there is a cardinality mismatch -
        // KDTREE_ERROR_INDEX is returned
        // Calls nearestPointIndexHelper()

    const Types::Points< T > points() const;
        // Returns the set of points represented by this KDTree. Used
        // primarily for testing.

    const std::string& type() const;
        // Returns type of this KDTree object

    // MANIPULATORS
    void copy( const KDTree& other );
        // Copies the value of other into this

    // ACCESSORS
    bool equals( const KDTree& other ) const;
        // Worker for equality - call this in child classes when overloading
        // == and != operator

    std::ostream& print( std::ostream& out ) const;
        // Prints the contents of the KDTree object in a easy to read
        // format

protected:
    virtual const KDHyperplane< T > chooseBestSplit(
            const Types::Indexes& indexes ) const;
        // To be overloaded by children when extending the vanilla KDTree
        // Serves as a heuristics in determining optimal hyperplane to split the
        // provided points as defined by the index array into m_points variable.


private:
    std::shared_ptr< KDNode< T > > build( const Types::Indexes& indexes );
        // Function that builds the recursive bisection of the tree, as
        // described by the assignment specification. Calls chooseBestSplit()
        // at each level of recursion until leaf nodes is reached.

    const size_t nearestPointIndexHelper(
            std::shared_ptr< KDNode< T > > root,
            const Types::Point< T >&       pointOfInterest,
            const size_t                   bestSoFarIndex ) const;
        // A recursive helper function, finds the closes point in to the
        // point of interest

    // The following allows creating of derived classes for test purposes
    // while not exposing the vital components in productions classes
protected:
    std::shared_ptr< KDNode< T > >     m_root;
        // Root node of this KD Tree

    Types::Points< T >                 m_points;
        // Points that the tree is built on

private:

    std::string                        m_type;
        // Type of the KDTree. Used primarily for debugging/logs
};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDTree< T >& rhs );

//============================================================================
//                  CREATORS
//============================================================================

template< typename T >
KDTree< T >::KDTree()
: m_type( Constants::KDTREE_SIMPLE_VARIETY )
{
    // nothing to do here
}

template< typename T >
KDTree< T >::KDTree( const Types::Points< T >& points )
: m_points( points )
, m_type( Constants::KDTREE_SIMPLE_VARIETY )
{
    Types::Indexes globalIndexes;
    globalIndexes.reserve( m_points.size() );
    for ( size_t i = 0; i < m_points.size(); ++i )
    {
        globalIndexes.push_back( i );
    }

    m_root = build( globalIndexes );
}

template< typename T >
KDTree< T >::KDTree( const KDTree& other )
: m_type( Constants::KDTREE_SIMPLE_VARIETY )
{
    copy( other );
}

template< typename T >
KDTree< T >::~KDTree()
{
    // nothing to do here
}

//============================================================================
//                  OPERATORS
//============================================================================

template< typename T >
KDTree< T >&
KDTree< T >::operator=( const KDTree< T >& other )
{
    copy( other );
    return *this;
}

template< typename T >
bool
KDTree< T >::operator==( const KDTree< T >& other ) const
{
    return equals( other );
}

template< typename T >
bool KDTree< T >::operator!=(
        const KDTree< T >& other ) const
{
    return !equals( other );
}

//============================================================================
//                  PRIMARY INTERFACE
//============================================================================
template< typename T >
bool
KDTree< T >::serialize( const std::string& filename ) const
{
    std::cout << "Implement me!" << std::endl;
    return false;
}

template< typename T >
bool
KDTree< T >::deserialize( const std::string& filename )
{
    std::cout << "Implement me!" << std::endl;
    return false;
}

template< typename T >
const Types::Point< T >
KDTree< T >::nearestPoint( const Types::Point< T >& pointOfInterest ) const
{
    const size_t index = nearestPointIndex( pointOfInterest );
    if ( Constants::KDTREE_ERROR_INDEX == index )
    {
        return Types::Point< T >();
    }

    return m_points[ index ];
}

template< typename T >
size_t
KDTree< T >::nearestPointIndex(
        const Types::Point< T >& pointOfInterest ) const
{
    return nearestPointIndexHelper( m_root,
                                    pointOfInterest,
                                    Constants::KDTREE_ERROR_INDEX );
}

template< typename T >
const Types::Points< T >
KDTree< T >::points() const
{
    return m_points;
}

template< typename T >
const std::string&
KDTree< T >::type() const
{
    return m_type;
}

template< typename T >
const KDHyperplane< T >
KDTree< T >::chooseBestSplit( const Types::Indexes& indexes ) const
{
    Types::Points< T > tempPoints;
    tempPoints.reserve( indexes.size() );

    for ( typename Types::Indexes::const_iterator it = indexes.cbegin();
          it != indexes.cend(); ++it )
    {
        tempPoints.push_back( m_points[ ( *it ) ] );
    }

    const size_t axis  = Utils::axisOfHighestVariance( tempPoints );
    const T      value = Utils::medianValueInAxis( tempPoints, axis );

    return KDHyperplane< T >( axis, value );
}

template< typename T >
std::shared_ptr< KDNode< T > >
KDTree< T >::build( const Types::Indexes& indexes )
{
    // Sanity
    if ( !indexes.size() )
    {
        std::cerr << "KDTree< T >::build() points container is empty"
                  << std::endl;
        return std::shared_ptr< KDNode< T > >( nullptr );
    }

    // Base Case
    if ( indexes.size() == 1u )
    {
        // Make a leaf node
        typename Types::Indexes::const_iterator it = indexes.cbegin();
        return std::shared_ptr< KDNode< T > >(
                new KDNode< T >( ( *it ) ) );
    }

    // Recursive case
    const KDHyperplane< T > hyperplane = chooseBestSplit( indexes );

    Types::Indexes leftIndexes;
    Types::Indexes rightIndexes;

    for ( typename Types::Indexes::const_iterator it = indexes.cbegin();
          it != indexes.cend(); ++it )
    {
        Types::Point< T > point = m_points[ (*it) ];

        if ( point[ hyperplane.hyperplaneIndex() ] < hyperplane.value() )
        {
            leftIndexes.push_back( *it );
        }
        else
        {
            rightIndexes.push_back( *it );
        }
    }

    std::shared_ptr< KDNode< T > > leftSubtree(  build( leftIndexes  ) );
    std::shared_ptr< KDNode< T > > rightSubtree( build( rightIndexes ) );

    return std::shared_ptr< KDNode< T > >( new KDNode< T >( hyperplane,
                                                            leftSubtree,
                                                            rightSubtree ) );
}

template< typename T >
const size_t
KDTree< T >::nearestPointIndexHelper(
        std::shared_ptr< KDNode< T > > root,
        const Types::Point< T >&       pointOfInterest,
        const size_t                   bestSoFarIndex ) const
{
    // Base case
    if ( nullptr == root )
    {
        return Constants::KDTREE_ERROR_INDEX;
    }

    if ( root->isLeaf() )
    {
        // Sanity
        if ( Constants::KDTREE_ERROR_INDEX == root->leafPointIndex() )
        {
            std::cerr << "Internal logic error, root " << root << " must not "
                      << "have Constants::KDTREE_ERROR_INDEX index"
                      << std::endl;
            return root->leafPointIndex();
        }

        // Initial greedy search
        if ( Constants::KDTREE_ERROR_INDEX == bestSoFarIndex )
        {
            return root->leafPointIndex();
        }

        const Types::Point< T >& leafPoint =
                m_points[ root->leafPointIndex() ];

        const double distance = Utils::distance< T >( leafPoint,
                                                      pointOfInterest );

        if ( Constants::KDTREE_INVALID_DISTANCE == distance )
        {
            std::cerr << "Point cardinality mismatch. Point of interest has"
                      << "cardinality = " << pointOfInterest.size() << " "
                      << "while points stored in the tree have "
                      << "cardinality = " << leafPoint << " "
                      << std::endl;
            return Constants::KDTREE_ERROR_INDEX;
        }

        if ( distance < Utils::distance< T >( m_points[ bestSoFarIndex ],
                                              pointOfInterest ) )
        {
            return root->leafPointIndex();
        }
        else
        {
            return bestSoFarIndex;
        }
    }

    // Sanity
    if ( pointOfInterest.size() <= root->hyperplane().hyperplaneIndex() )
    {
        std::cerr << "Point cardinality mismatch. Point of interest has"
                  << "cardinality = " << pointOfInterest.size() << " "
                  << "while points stored in the tree have "
                  << "cardinality of at least = "
                  << root->hyperplane().hyperplaneIndex() << " "
                  << std::endl;
        return Constants::KDTREE_ERROR_INDEX;
    }

    // Recursive case
    std::shared_ptr< KDNode< T > > greedy;
    std::shared_ptr< KDNode< T > > other;

    if ( pointOfInterest[ root->hyperplane().hyperplaneIndex() ] <
                root->hyperplane().value() )
    {
        greedy = root->left();
        other = root->right();
    }
    else
    {
        greedy = root->right();
        other = root->left();
    }

    // First search greedily
    const size_t greedyBestIndex = nearestPointIndexHelper( greedy,
                                                            pointOfInterest,
                                                            bestSoFarIndex );
    // If the distance to the greedy best is bigger than distance to the
    // hyperplane at this node, search the other partition as well
    if ( Utils::distance< T >( pointOfInterest, root->hyperplane() ) <
         Utils::distance< T >( pointOfInterest, m_points[ greedyBestIndex ] ) )
    {
        return nearestPointIndexHelper( other,
                                        pointOfInterest,
                                        greedyBestIndex );
    }

    return greedyBestIndex;
}

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDTree< T >::copy( const KDTree< T >& other )
{
    m_points = other.points();

    Types::Indexes globalIndexes;
    globalIndexes.reserve( m_points.size() );
    for ( size_t i = 0; i < m_points.size(); ++i )
    {
        globalIndexes.push_back( i );
    }

    m_root = build( globalIndexes );
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDTree< T >::equals( const KDTree< T >& other ) const
{
    return ( ( other.type()    == m_type   ) &&
             ( other.points()  == m_points ) );
}

template< typename T >
std::ostream&
KDTree< T >::print( std::ostream& out ) const
{
    out << "KDTree:[ "
        << "implementation type = '" << m_type          << "', "
        << "num points stored = "    << m_points.size() << " ] ";

    return out;
}

//============================================================================
//                  INDEPENDENT OPERATORS
//============================================================================
template< typename T >
std::ostream& operator<<( std::ostream& lhs, const KDTree< T >& rhs )
{
    return rhs.print( lhs );
}

} // namespace datastructures

#endif // KDTREE_H