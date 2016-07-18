#ifndef KDTREE_H
#define KDTREE_H

#include <memory>

#include "kdtree_types.h"
#include "kdtree_node.h"
#include "kdtree_hyperplane.h"
#include "kdtree_utils.h"

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
        // Calls nearestPointHelper()

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
            const Types::Points< T >& points ) const;
        // To be overloaded by children when extending the vanilla KDTree
        // Serves as a heuristics in determining optimal hyperplane to split the
        // provided points.

private:
    std::shared_ptr< KDNode< T > > build( const Types::Points< T > points );
        // Function that builds the recursive bisection of the tree, as
        // described by the assignment specification. Calls chooseBestSplit()
        // at each level of recursion until leaf nodes is reached.

    void reassemblePoints( std::shared_ptr< KDNode< T > > node,
                           Types::Points< T >& points ) const;
        // A recursive helper function. Assemble all the stored points in
        // the tree into a container

    const Types::Point< T > nearestPointHelper(
            std::shared_ptr< KDNode< T > > root,
            const Types::Point< T >& pointOfInterest,
            const Types::Point< T >& bestSoFar ) const;
        // A recursive helper function, finds the closes point in to the
        // point of interest

protected:
    std::shared_ptr< KDNode< T > >     m_root;
        // Root node of this KD Tree

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
: m_type( Constants::KDTREE_SIMPLE_VARIETY )
{
    m_root = build( points );
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
    return nearestPointHelper( m_root,
                               pointOfInterest,
                               Types::Point< T >() );
}

template< typename T >
const Types::Points< T >
KDTree< T >::points() const
{
    Types::Points< T > points;
    reassemblePoints( m_root, points );
    return points;
}

template< typename T >
const std::string&
KDTree< T >::type() const
{
    return m_type;
}

template< typename T >
const KDHyperplane< T >
KDTree< T >::chooseBestSplit( const Types::Points< T >& points ) const
{
    const size_t axis  = Utils::axisOfHighestVariance( points );
    const T      value = Utils::medianValueInAxis( points, axis );

    return KDHyperplane< T >( axis, value );
}

template< typename T >
std::shared_ptr< KDNode< T > >
KDTree< T >::build( const Types::Points< T > points )
{
    //TODO: remove
    //std::cout << "=======================" << std::endl;
    //std::cout << "Entering create on : " << points << std::endl;
    // Sanity
    if ( !points.size() )
    {
        std::cerr << "KDTree< T >::build() points container is empty"
                  << std::endl;
        return std::shared_ptr< KDNode< T > >( nullptr );
    }

    // Base Case
    if ( points.size() == 1u )
    {
        //TODO: remove
        //std::cout << "Base case, returning " << std::endl;

        // Make a leaf node
        typename Types::Points< T >::const_iterator it = points.cbegin();
        return std::shared_ptr< KDNode< T > >(
                new KDNode< T >( ( *it ) ) );
    }

    // Recursive case
    const KDHyperplane< T > hyperplane = chooseBestSplit( points );

    //TODO: remove
    //std::cout << hyperplane << std::endl;

    Types::Points< T > leftPoints;
    Types::Points< T > rightPoints;

    for ( typename Types::Points< T >::const_iterator it = points.cbegin();
          it != points.cend(); ++it )
    {
        if ( ( *it )[ hyperplane.hyperplaneIndex() ] < hyperplane.value() )
        {
            leftPoints.insert( *it );
        }
        else
        {
            rightPoints.insert( *it );
        }
    }

    std::shared_ptr< KDNode< T > > leftSubtree(  build( leftPoints  ) );
    std::shared_ptr< KDNode< T > > rightSubtree( build( rightPoints ) );

    return std::shared_ptr< KDNode< T > >( new KDNode< T >( hyperplane,
                                                            leftSubtree,
                                                            rightSubtree ) );
}

template< typename T >
void
KDTree< T >::reassemblePoints( std::shared_ptr< KDNode< T > > node,
                               Types::Points< T >& points ) const
{
    // Base Case
    if ( nullptr == node )
    {
        return;
    }

    if ( node->isLeaf() )
    {
        points.insert( node->leafPoint() );
    }

    // Recursive Case
    reassemblePoints( node->left(), points );
    reassemblePoints( node->right(), points );
}
template< typename T >
const Types::Point< T >
KDTree< T >::nearestPointHelper( std::shared_ptr< KDNode< T > > root,
                                 const Types::Point< T >& pointOfInterest,
                                 const Types::Point< T >& bestSoFar ) const
{
    //TODO: remove
//    std::cout << "================" << std::endl;
//    std::cout << "Searching for " << pointOfInterest << std::endl;
//    std::cout << "Best so far " << bestSoFar << std::endl;

    // Base case
    if ( nullptr == root )
    {
//        std::cout << "    root is empty, returning empty point"  << std::endl;
        return Types::Point< T >();
    }

    if ( root->isLeaf() )
    {
//        std::cout << "    *** root it leaf" << root->leafPoint() << std::endl;

        // Initial greedy search
        if ( bestSoFar.empty() )
        {
//            std::cout << "    best so far is empty, returning leaf" << std::endl;
//            std::cout << "==== done ======" << std::endl;
            return root->leafPoint();
        }

        const double distance = Utils::distance< T >( root->leafPoint(),
                                                      pointOfInterest );

//        std::cout << "    distance : " << distance << std::endl;

        if ( Constants::KDTREE_INVALID_DISTANCE == distance )
        {
            std::cerr << "Point cardinality mismatch. Point of interest has"
                      << "cardinality = " << pointOfInterest.size() << " "
                      << "while points stored in the tree have "
                      << "cardinality = " << root->leafPoint().size() << " "
                      << std::endl;

//            std::cout << "==== done ======" << std::endl;
            return Types::Point< T >();
        }

        if ( distance < Utils::distance< T >( bestSoFar, pointOfInterest ) )
        {
//            std::cout << "    leaf is new best " << root->leafPoint() << std::endl;
//            std::cout << "==== done ======" << std::endl;
            return root->leafPoint();
        }
        else
        {
//            std::cout << "    old best is better " << bestSoFar << std::endl;
//            std::cout << "==== done ======" << std::endl;
            return bestSoFar;
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
        //std::cout << "==== done ======" << std::endl;
        return Types::Point< T >();
    }

    // Recursive case
    std::shared_ptr< KDNode< T > > greedy;
    std::shared_ptr< KDNode< T > > other;

//    std::cout << "    *** root it not leaf, " << root->hyperplane() << std::endl;

    if ( pointOfInterest[ root->hyperplane().hyperplaneIndex() ] <
                root->hyperplane().value() )
    {
  //      std::cout << "        going left first" << std::endl;
        greedy = root->left();
        other = root->right();
    }
    else
    {
//        std::cout << "        going right first" << std::endl;
        greedy = root->right();
        other = root->left();
    }

    // First search greedily
    const Types::Point< T >& greedyBest = nearestPointHelper( greedy,
                                                              pointOfInterest,
                                                              bestSoFar );

//    std::cout << "        greedy best " << greedyBest << std::endl;

    const double greedyShortestDist = Utils::distance< T >( pointOfInterest,
                                                            greedyBest );

//    std::cout << "        dist to it " << greedyShortestDist << std::endl;

    // If the distance to the greedy best is bigger than distance to the
    // hyperplane at this node, search the other partition as well
    if ( Utils::distance< T >( pointOfInterest, root->hyperplane() ) <
            greedyShortestDist )
    {
//        std::cout << "       ** may be able to find and alternative " << std::endl;
        //TODO: remove
        const Types::Point< T >& alternative =
                nearestPointHelper( other,
                                    pointOfInterest,
                                    greedyBest );

//        std::cout << "        alternative ? " << ( ( alternative != greedyBest ) ? "yes" : "no" )
//                  << std::endl;

//        std::cout << "        alternative " << alternative << std::endl;
//        std::cout << "==== done ======" << std::endl;
        return alternative;
    }

//    std::cout << "    returning " << greedyBest << std::endl;
//    std::cout << "==== done ======" << std::endl;
    return greedyBest;
}

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDTree< T >::copy( const KDTree< T >& other )
{
    m_root = build( other.points() );
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDTree< T >::equals( const KDTree< T >& other ) const
{
    return ( ( other.type()    == m_type ) &&
             ( other.points()  == points() ) );
}

template< typename T >
std::ostream&
KDTree< T >::print( std::ostream& out ) const
{
    out << "KDTree:[ "
        << "implementation type = '" << m_type          << "', "
        << "num points stored = "    << points().size() << " ] ";

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