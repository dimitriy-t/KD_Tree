#ifndef KDTREE_H
#define KDTREE_H

#include "kdtree_node.h"

// @Purpose
//
// This is a base class for a simple KDTree datastructure implementation

namespace datastructures {

template< typename < T > >
class KDTree {
public:

    KDTree();
        // default ctor

    KDTree( Points< T > points );
        // constructor, throws in case points are of different length

    ~KDTree();
        // default dtor

    // OPERATORS
    KDTree& operator=( const KDTree& other );
        // assignment operator. Calls copy; do this in child classes
        // when overloaded.

    bool operator==( const KDTree& other ) const;
        // equality. Calls equals, do this in child classes
        // when overloaded.

    bool operator!=( const KDTree& other ) const;
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
    size_t                             m_hyperplaneIndex;
        // defines the index of the hyperplane

    T                                  m_value;
        // position of the hyperplane, left subtree is less or equal, right
        // subtree is greate

    std::shared_ptr< KDTree< T > >     m_left;
        // left subtree

    std::shared_ptr< KDTree< T > >     m_right;
        // right subtree
};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDTree< T >& rhs );
// TODO: move to types, works?
template < typename T >
using Point< T > = std::vector< T >;

template < typename T >
using Points< T > = std::set< Point < T > >;

};
	
} // namespace datastructures

#endif // KDTREE_H