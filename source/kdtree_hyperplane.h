#ifndef KDTREE_HYPERPLANE_H
#define KDTREE_HYPERPLANE_H

#include <iostream>
#include <sstream>
#include <string>

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

    const std::string serialize() const;
        // Returns the serialized hyperplane as a string

    bool deserialize( const std::string& serialized );
        // Loads the contents of the hyperplane from the serialized
        // representation
        // Returns true on success and false otherwise.

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
: m_hyperplaneIndex( Constants::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX )
, m_value( static_cast< T >(
                     Constants::KDTREE_UNINITIALIZED_HYPERPLANE_VALUE ) )
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

template< typename T >
const std::string
KDHyperplane< T >::serialize() const
{
    std::ostringstream serialized;
    serialized << m_hyperplaneIndex << " " << m_value;
    return serialized.str();
}

template< typename T >
bool
KDHyperplane< T >::deserialize( const std::string& serialized )
{
    if ( serialized.empty() )
    {
        std::cerr << "Empty string passed to KDHyperplane::deserialize()"
                  << std::endl;
        return false;
    }

    size_t pos = 0;
    int val1;

    try
    {
        val1 = std::stoi( serialized , &pos );
    }
    catch ( std::exception e )
    {
        std::cerr << "Exception encountered during first val parsing in"
                  << "KDHyperplane::deserialize()"
                  << "serialized : '" << serialized << "', "
                  << "what : '" << e.what() << "'"
                  << std::endl;
                  return false;
    }
    catch ( ... )
    {
        std::cerr << "Unknown exception encountered during first val parsing "
                  << "in KDHyperplane::deserialize()"
                  << "serialized : '" << serialized << "', "
                  << std::endl;
        return false;
    }

    if ( val1 < 0 )
    {
        std::cerr << "Negative hyperplane index passed to "
                  << "KDHyperplane::deserialize(), positive index value"
                  << "expected"
                  << "serialized : '" << serialized << "'"
                  << std::endl;
        return false;
    }

    if ( serialized.length() == pos )
    {
        std::cerr << "Negative hyperplane index passed to "
                  << "KDHyperplane::deserialize(), two values expected"
                  << "serialized : '" << serialized << "'"
                  << std::endl;
        return false;
    }

    const std::string second = serialized.substr( pos );
    double val2;

    try
    {
        val2 = std::stof( second , &pos );
    }
    catch ( std::exception e )
    {
        std::cerr << "Exception encountered during second val parsing in"
                  << "KDHyperplane::deserialize()"
                  << "serialized : '" << serialized << "', "
                  << "what : '" << e.what() << "'"
                  << std::endl;
                  return false;
    }
    catch ( ... )
    {
        std::cerr << "Unknown exception encountered during second val parsing "
                  << "in KDHyperplane::deserialize()"
                  << "serialized : '" << serialized << "', "
                  << std::endl;
                  return false;
    }

    m_hyperplaneIndex = static_cast< size_t >( val1 );
    m_value           = static_cast< T >( val2 );

    return true;
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
    out << "KDHyperplane:[ "
        << "hyperplane index = '" << std::dec << m_hyperplaneIndex << "', "
        << "value = '"            << std::dec << m_value           << "' ] ";
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