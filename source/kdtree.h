#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <set>
#include <memory>

#include "kdtree_node.h"


// @Purpose
//
// This is a base class for a simple KDTree datastructure implementation

namespace datastructures {

template < typename T >
using Point = std::vector< T >;

template < typename T >
using Points = std::set< Point < T > >;

template< typename T >
class KDTree {
public:

    KDTree();
        // default ctor

    KDTree( const KDTree< T >& other );
        // Copy constructor, copies the pointer contained in other, not the
        // bisection
        // Calls build() helper

    KDTree( const Points< T >& points );
        // constructor, throws in case points are of different length
        // Calls build() helper

    ~KDTree();
        // default dtor

    // OPERATORS
    KDTree& operator=( const KDTree< T >& other );
        // assignment operator. Calls copy; do this in child classes
        // when overloaded.
        // Note that this operator will copy the the points contained within
        // the provided tree, yet will build its own bisecting structure of the
        // space using own chooseBestSplit() implementation
        // Calls build() helper

    bool operator==( const KDTree< T >& other ) const;
        // equality. Calls equals, do this in child classes
        // when overloaded.
        // Calls build() helper

    bool operator!=( const KDTree< T >& other ) const;
        // non-equality.  Calls equals, do this in child classes
        // when overloaded.

    // PRIMARY INTERFACE
    //TODO: throw?
    void serialize( const std::string& filename ) const;
        // writes the tree to the provided file location

    //TODO: throw?
    void deserialize( const std::string& filename );
        // loads the contents of the data via the contents of the file

    Point< T > nearestPoint( const Point< T > ) const;
        // returns the closes point in a tree to the point provided
        // in case the tree is empty - point itself is returned

protected:
    virtual Point< T > chooseBestSplit( Points< T > points,
                                        const size_t plane );
        // to be overloaded by children when extending the vanilla KDTree
        // Picks the best possible point out of the provided set in splitting
        // the tree in two for a given plane
        // 0 <= plane < cardinality of point space

    // MANIPULATORS
    void copy( const KDTree& other );
        // copies the value of other into this

    // ACCESSORS
    bool equals( const KDTree& other ) const;
        // worker for equality - call this in child classes when overloading
        // == and != operator

    std::ostream& print( std::ostream& out ) const;
        // Prints the contents of the KDTree object in a easy to read
        // format

private:
    void build();
        // Function that builds the recursive bisection of the tree, as
        // described by the assingmnet specification. Calls chooseBestSplit()

private:
    std::shared_ptr< KDNode< T > >     m_root;
        // Root node of this KD Tree

    Points< T >                        m_points;
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
KDTree< T >::KDTree( const Points< T >& points )
: m_points( points )
{
    std::cout << "Implement the rest!" << std::endl;
    build();
}

template< typename T >
KDTree< T >::KDTree( const KDTree& other )
{
    copy( other );
    build();
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
    build();
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
void
KDTree< T >::serialize( const std::string& filename ) const
{
    std::cout << "Implement me!" << std::endl;
}

template< typename T >
void
KDTree< T >::deserialize( const std::string& filename )
{
    std::cout << "Implement me!" << std::endl;
}

template< typename T >
Point< T >
KDTree< T >::nearestPoint( const Point< T > ) const
{
    std::cout << "Implement me!" << std::endl;
    return Point< T >();
}

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