#ifndef KDTREE_NODE_H
#define KDTREE_NODE_H

#include <iostream>
#include <memory>
#include <sstream>

#include "kdtree_types.h"
#include "kdtree_constants.h"
#include "kdtree_hyperplane.h"

namespace datastructures {

// PURPOSE:
//
// A class that defines individual notes within a KD-Tree. Used to
// represent both leaf and non-leaf nodes.
//
template< typename T >
class KDNode {
public:
    // CREATORS
    KDNode();
    // Default constructor

    KDNode( const KDHyperplane< T >&               hyperplane,
            const std::shared_ptr< KDNode< T > >&  left,
            const std::shared_ptr< KDNode< T > >&  right );
        // Non-leaf Constructor

    KDNode( const Types::Point< T >* leaf );
        // Leaf Constructor

    KDNode( const KDNode& other );
        // Copy constructor, calls copy().

    virtual ~KDNode();
        // Destructor

    // OPERATORS
    KDNode& operator=( const KDNode& other );
        // Assignment operator. Calls copy.
        // Note that this operator performs a shallow copy as its
        // use is targeted at containers.

    bool operator==( const KDNode& other ) const;
        // Equality. Calls equals.

    bool operator!=( const KDNode& other ) const;
        // Non-equality. Calls equals.

    // PRIMARY INTERFACE
    const KDHyperplane< T >& hyperplane() const;
        // Returns diving hyperplane represented by this node

    std::shared_ptr< KDNode< T > > left() const;
        // Return shared pointer to the left subtree

    std::shared_ptr< KDNode< T > > right() const;
        // Return shared pointer to the right subtree

    //TODO: think about making this a special leaf node class that always has a reference to a Point
    const Types::Point< T >* leafPointPtr() const;
        // Return pointer of the point stored in KDTree that this node
        // represents. Note that non-leaf nodes will return
        // nullptr

    // MANIPULATORS
    void copy( const KDNode& other );
        // Copies the value of other into this

    // ACCESSORS
    bool equals( const KDNode& other ) const;
        // Worker for equality - call this in child classes when overloading
        // == and != operator

    std::ostream& print( std::ostream& out ) const;
        // Prints the contents of the KDNode object in a easy to read
        // format

private:
    KDHyperplane< T >                  m_hyperplane;
        // Defines hyperplane of this node

    std::shared_ptr< KDNode< T > >     m_left;
        // Left subtree

    std::shared_ptr< KDNode< T > >     m_right;
        // Right subtree

    const Types::Point< T >*           m_leafPointPtr;
        // Pointer to leaf point in the KDTree. Note that KDNode is used to
        // index the points in a KDTree, but does not own the memory;
};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDNode< T >& rhs );

//============================================================================
//                  CREATORS
//============================================================================

template< typename T >
KDNode< T >::KDNode()
: m_left(         nullptr )
, m_right(        nullptr )
, m_leafPointPtr( nullptr )
{
    // nothing to do here
}

template< typename T >
KDNode< T >::KDNode( const KDHyperplane< T >&               hyperplane,
                     const std::shared_ptr< KDNode< T > >&  left,
                     const std::shared_ptr< KDNode< T > >&  right )
: m_hyperplane(   hyperplane )
, m_left(         left )
, m_right(        right )
, m_leafPointPtr( nullptr )
{
    // nothing to do here
}

template< typename T >
KDNode< T >::KDNode( const Types::Point< T >* leafPointPtr )
: m_left(         nullptr )
, m_right(        nullptr )
, m_leafPointPtr( leafPointPtr )
{
    // nothing to do here
}

template< typename T >
KDNode< T >::KDNode( const KDNode& other )
{
    copy( other );
}

template< typename T >
KDNode< T >::~KDNode()
{
    // nothing to do here
}

//============================================================================
//                  OPERATORS
//============================================================================

template< typename T >
KDNode< T >&
KDNode< T >::operator=( const KDNode< T >& other )
{
    copy( other );
    return *this;
}

template< typename T >
bool
KDNode< T >::operator==( const KDNode< T >& other ) const
{
    return equals( other );
}

template< typename T >
bool KDNode< T >::operator!=(
        const KDNode< T >& other ) const
{
    return !equals( other );
}

//============================================================================
//                  PRIMARY INTERFACE
//============================================================================
template< typename T >
const KDHyperplane< T >&
KDNode< T >::hyperplane() const
{
    return m_hyperplane;
}

template< typename T >
std::shared_ptr< KDNode< T > >
KDNode< T >::left() const
{
    return m_left;
}

template< typename T >
std::shared_ptr< KDNode< T > >
KDNode< T >::right() const
{
    return m_right;
}

template< typename T >
const Types::Point< T >*
KDNode< T >::leafPointPtr() const
{
    return m_leafPointPtr;
}

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDNode< T >::copy( const KDNode< T >& other )
{
    m_hyperplane   = other.hyperplane();
    m_left         = other.left();
    m_right        = other.right();
    m_leafPointPtr = other.leafPointPtr();
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDNode< T >::equals( const KDNode< T >& other ) const
{
    return ( ( other.hyperplane()   == m_hyperplane   ) &&
             ( other.left()         == m_left         ) &&
             ( other.right()        == m_right        ) &&
             ( other.leafPointPtr() == m_leafPointPtr ) );
}

template< typename T >
std::ostream&
KDNode< T >::print( std::ostream& out ) const
{
    out << "KDNode:["
        << "hyperplane = '"     << std::dec << m_hyperplane   << "', "
        << "left ptr = '"       << std::hex << m_left         << "', "
        << "right ptr = '"      << std::hex << m_right        << "', "
        << "leaf point ptr = '" << std::hex << m_leafPointPtr << "']";

    return out;
}

//============================================================================
//                  INDEPENDENT OPERATORS
//============================================================================
template< typename T >
std::ostream& operator<<( std::ostream& lhs, const KDNode< T >& rhs )
{
    return rhs.print( lhs );
}

} // close namespace datastructures

#endif // KDTREE_NODE_H