#ifndef KDTREE_HYPERPLANE_H
#define KDTREE_HYPERPLANE_H

#include <iostream>
#include <sstream>

#include "kdtree_types.h"
#include "kdtree_constants.h"

namespace datastructures {

// PURPOSE:
//
// A class that defines a hyperplane splitting the space
//
template< typename T >
class KDHyperplane {
public:
    // CREATORS
    KDHyperplane();
    // Default constructor

    KDHyperplane( const size_t                           hyperplaneIndex,
                  const T                                value );
    // Constructor

    KDHyperplane( const KDHyperplane& other );
        // Copy constructor, calls copy().

    virtual ~KDHyperplane();
        // Destructor

    // OPERATORS
    KDHyperplane& operator=( const KDHyperplane& other );
        // Assignment operator. Calls copy.
        // Note that this operator performs a shallow copy as its
        // use is targeted at containers.

    bool operator==( const KDHyperplane& other ) const;
        // Equality. Calls equals.

    bool operator!=( const KDHyperplane& other ) const;
        // Non-equality. Calls equals.

    // PRIMARY INTERFACE
    const size_t hyperplaneIndex() const;
        // Returns index of the hyperplane defined by this node

    const T value() const;
        // Return value of this node - i.e. position of the hyperplane
        // defined by this node.
        // Note that value is set to static_cast< T >( 0 ) by the
        // default dtor

    // MANIPULATORS
    void copy( const KDHyperplane& other );
        // Copies the value of other into this

    // ACCESSORS
    bool equals( const KDHyperplane& other ) const;
        // Worker for equality - call this in child classes when overloading
        // == and != operator

    std::ostream& print( std::ostream& out ) const;
        // Prints the contents of the KDHyperplane object in a easy to read
        // format

private:
    size_t  m_hyperplaneIndex;
        // Defines the index of the hyperplane

    T       m_value;
        // Position of the hyperplane, left subtree is less or equal, right
        // subtree is greater
};

// INDEPENDENT OPERATORS
template< typename T >
std::ostream& operator<<( std::ostream& lhs,
                          const KDHyperplane< T >& rhs );

//============================================================================
//                  CREATORS
//============================================================================

template< typename T >
KDHyperplane< T >::KDHyperplane()
: m_hyperplaneIndex( Defaults::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX )
, m_value( static_cast< T >(
                   Defaults::KDTREE_UNINITIALIZED_HYPERPLANE_VALUE ) )
{
    // nothing to do here
}

template< typename T >
KDHyperplane< T >::KDHyperplane( const size_t hyperplaneIndex,
                                 const T      value )
: m_hyperplaneIndex( hyperplaneIndex )
, m_value(           value )
{
    // nothing to do here
}

template< typename T >
KDHyperplane< T >::KDHyperplane( const KDHyperplane& other )
{
    copy( other );
}

template< typename T >
KDHyperplane< T >::~KDHyperplane()
{
    // nothing to do here
}

//============================================================================
//                  OPERATORS
//============================================================================

template< typename T >
KDHyperplane< T >&
KDHyperplane< T >::operator=( const KDHyperplane< T >& other )
{
    copy( other );
    return *this;
}

template< typename T >
bool
KDHyperplane< T >::operator==( const KDHyperplane< T >& other ) const
{
    return equals( other );
}

template< typename T >
bool KDHyperplane< T >::operator!=( const KDHyperplane< T >& other ) const
{
    return !equals( other );
}

//============================================================================
//                  PRIMARY INTERFACE
//============================================================================
template< typename T >
const size_t
KDHyperplane< T >::hyperplaneIndex() const
{
    return m_hyperplaneIndex;
}

template< typename T >
const T
KDHyperplane< T >::value() const
{
    return m_value;
}

//============================================================================
//                  MANIPULATORS
//============================================================================

template< typename T >
void
KDHyperplane< T >::copy( const KDHyperplane< T >& other )
{
    m_hyperplaneIndex = other.hyperplaneIndex();
    m_value           = other.value();
}

//============================================================================
//                  ACCESSORS
//============================================================================

template< typename T >
bool
KDHyperplane< T >::equals(
        const KDHyperplane< T >& other ) const
{
    return ( ( other.hyperplaneIndex() == m_hyperplaneIndex ) &&
             ( other.value()           == m_value      ) );
}

template< typename T >
std::ostream&
KDHyperplane< T >::print( std::ostream& out ) const
{
    out << "KDHyperplane:["
        << "hyperplane index = '" << std::dec << m_hyperplaneIndex << "', "
        << "value = '"            << std::dec << m_value           << "'] ";
    return out;
}

//============================================================================
//                  INDEPENDENT OPERATORS
//============================================================================
template< typename T >
std::ostream& operator<<( std::ostream& lhs, const KDHyperplane< T >& rhs )
{
    return rhs.print( lhs );
}

} // close namespace datastructures

#endif // KDTREE_HYPERPLANE_H