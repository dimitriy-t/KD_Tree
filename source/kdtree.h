#ifndef KDTREE_H
#define KDTREE_H

#include <memory>

#include "kdtree_types.h"
#include "kdtree_node.h"
#include "kdtree_hyperplane.h"

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

    const Types::Point< T >& nearestPoint(
            const Types::Point< T >& point ) const;
        // Returns const ref the closes point in a tree to the point provided
        // in case the tree is empty - point itself is returned.

    const Types::Points< T >& points() const;
        // Returns the set of points represented by this KDTree. Used
        // primarily for testing.

protected:
    //TODO: might need to include exclusion plane
    //TODO: this might need to have points only
    virtual const KDHyperplane< T > chooseBestSplit(
            const Types::Points< T >& points,
            const size_t plane ) const;
        // To be overloaded by children when extending the vanilla KDTree
        // Serves as a heuristics in determining optimal hyperplane to split the
        // provided points.

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

private:
    //TODO: fix this part in a nice way!
//    void build( std::shared_ptr< KDNode< T > > root,
//                Types::Points< T >             points );
        // Function that builds the recursive bisection of the tree, as
        // described by the assignment specification. Calls chooseBestSplit()
        // at each level of recursion until leaf nodes is reached.

private:
    std::shared_ptr< KDNode< T > >     m_root;
        // Root node of this KD Tree

    Types::Points< T >                 m_points;
        // A list of all points existing in a tree

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
{
    // nothing to do here
}

template< typename T >
KDTree< T >::KDTree( const Types::Points< T >& points )
: m_points( points )
{
    std::cout << "Implement the rest!" << std::endl;
   // build();
}

template< typename T >
KDTree< T >::KDTree( const KDTree& other )
{
    copy( other );
  //  build();
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
   // build();
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
const Types::Point< T >&
KDTree< T >::nearestPoint( const Types::Point< T >& point ) const
{
    std::cout << "Implement me!" << std::endl;
    return point;
}

template< typename T >
const Types::Points< T >&
KDTree< T >::points() const
{
    return m_points;
}
template< typename T >
const KDHyperplane< T >
KDTree< T >::chooseBestSplit( const Types::Points< T >& points,
                              const size_t plane ) const
{
    std::cout << "Implement me!" << std::endl;
    return KDHyperplane< T >();
}

//template< typename T >
//void
//KDTree< T >::build()
//{
//    std::cout << "Implement me!" << std::endl;
//}

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDTree< T >::copy( const KDTree< T >& other )
{
    std::cout << "Implement me!" << std::endl;
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDTree< T >::equals(
        const KDTree< T >& other ) const
{
    std::cout << "Implement me!" << std::endl;
    return false;
}

template< typename T >
std::ostream&
KDTree< T >::print( std::ostream& out ) const
{
    std::cout << "Implement me!" << std::endl;

    out << "KDTree:["
        << "']";

    return out;
}

//============================================================================
//                  INDEPENDENT OPERATORS
//============================================================================
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDTree< T >& rhs )
{
    return rhs.print( lhs );
}

} // namespace datastructures

#endif // KDTREE_H