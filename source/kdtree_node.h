#ifndef KDTREE_NODE_H
#define KDTREE_NODE_H

#include <iostream>
#include <memory>
#include <limits>
#include <sstream>

#include "kdtree_types.h"
#include "kdtree_constants.h"

namespace datastructures {

// PURPOSE:
//
// A class that defines individual notes within a KD-Tree
//
template< typename T >
class KDNode {
public:

    // CREATORS
    KDNode();
        // default constructor

    //TODO: implement
    KDNode( const size_t                           hyperplaneIndex,
            const T                                value,
            const std::shared_ptr< KDNode< T > >&  left,
            const std::shared_ptr< KDNode< T > >&  right );
        // constructor

    KDNode( const KDNode& other );
        // copy constructor, calls copy().

    virtual ~KDNode();
        // destructor

    // OPERATORS
    KDNode& operator=( const KDNode& other );
        // assignment operator. Calls copy; do this in child classes
        // when overloaded.

    bool operator==( const KDNode& other ) const;
        // equality. Calls equals, do this in child classes
        // when overloaded.

    bool operator!=( const KDNode& other ) const;
        // non-equality.  Calls equals, do this in child classes
        // when overloaded.

    // PRIMARY INTERFACE
    size_t hyperplaneIndex() const;
        // returns index of the hyperplane defined by this node

    T value() const;
        // return value of this node - i.e. position of the hyperplane
        // defined by this node

    std::shared_ptr< KDNode< T > > left() const;
        // return shared pointer to the left subtree

    std::shared_ptr< KDNode< T > > right() const;
        // return shared pointer to the right subtree

    // MANIPULATORS
    void copy( const KDNode& other );
        // copies the value of other into this

    // ACCESSORS
    bool equals( const KDNode& other ) const;
        // worker for equality - call this in child classes when overloading
        // == and != operator

    std::ostream& print( std::ostream& out ) const;
        // Prints the contents of the KDNode object in a easy to read
        // format

private:
    size_t                             m_hyperplaneIndex;
        // defines the index of the hyperplane

    T                                  m_value;
        // position of the hyperplane, left subtree is less or equal, right
        // subtree is greate

    std::shared_ptr< KDNode< T > >     m_left;
        // left subtree

    std::shared_ptr< KDNode< T > >     m_right;
        // right subtree
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
: m_hyperplaneIndex( std::numeric_limits< size_t >::max() )
, m_value( std::numeric_limits< T >::max() )
, m_left( NULL )
, m_right( NULL )
{
    // nothing to do here
}

template< typename T >
KDNode< T >::KDNode( const size_t                           hyperplaneIndex,
                     const T                                value,
                     const std::shared_ptr< KDNode< T > >&  left,
                     const std::shared_ptr< KDNode< T > >&  right )
: m_hyperplaneIndex( hyperplaneIndex )
, m_value( value )
, m_left( left)
, m_right( right )
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
size_t
KDNode< T >::hyperplaneIndex() const
{
    return m_hyperplaneIndex;
}

template< typename T >
T
KDNode< T >::value() const
{
    return m_value;
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

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDNode< T >::copy( const KDNode< T >& other )
{
    m_hyperplaneIndex = other.hyperplaneIndex();
    m_value           = other.value();
    m_left            = other.left();
    m_right           = other.right();
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDNode< T >::equals(
        const KDNode< T >& other ) const
{
    return ( ( other.hyperplaneIndex() == m_hyperplaneIndex ) &&
             ( other.value()           == m_value           ) &&
             ( other.left()            == m_left            ) &&
             ( other.right()           == m_right           ) );
}

template< typename T >
std::ostream&
KDNode< T >::print( std::ostream& out ) const
{
    out << "KDNode:["
        << "hyperplane index = '" << m_hyperplaneIndex   << "', "
        << "value = '"            << m_value             << "', "
        << "left ptr = '"         << std::hex << m_left  << "', "
        << "right ptr = '"        << std::hex << m_right << "']";

    return out;
}

//============================================================================
//                  INDEPENDENT OPERATORS
//============================================================================
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDNode< T >& rhs )
{
    return rhs.print( lhs );
}

} // close namespace datastructures

#endif // KDTREE_NODE_H