#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree_constants.h"
#include "kdtree_node.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// LOCAL TYPES AND DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( KDNode, TestZero )
{
    // initial object
    KDNode< int > zero;

    ASSERT_TRUE( zero == zero );
    ASSERT_TRUE( !( zero != zero ) );
    ASSERT_TRUE( zero.equals( zero ) );

    // Empty configs must be equivalent
    KDNode< int > zero2;

    ASSERT_TRUE( zero == zero2 );
    ASSERT_TRUE( !( zero != zero2 ) );
    ASSERT_TRUE( zero.equals( zero2 ) );

    // copy of initial object
    KDNode< int > zeroCopy( zero );
    ASSERT_TRUE( zero == zeroCopy );
    ASSERT_TRUE( !( zero != zeroCopy ) );
    ASSERT_TRUE( zero.equals( zeroCopy ) );

    // assign of initial object
    KDNode< int > zeroAssign;
    zeroAssign = zero;
    ASSERT_TRUE( zero == zeroAssign );
    ASSERT_TRUE( !( zero != zeroAssign ) );
    ASSERT_TRUE( zero.equals( zeroAssign ) );
}

TEST( KDNode, TestUninitializedState )
{
    KDNode< int > dummyNode;

    ASSERT_EQ( dummyNode.hyperplaneIndex(),
        Defaults::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX );
    ASSERT_EQ( dummyNode.left(), nullptr );
    ASSERT_EQ( dummyNode.left(), nullptr );
    ASSERT_EQ( dummyNode.leafIndex(),
        Defaults::KDTREE_NONLEAF_INDEX );
}

TEST( KDNode, Sanity )
{
    const size_t                             hyperplaneIndex = 1u;
    const int                                hyperplaneValue = 2;
    const std::shared_ptr< KDNode< int > >   left( new KDNode< int >() );
    const std::shared_ptr< KDNode< int > >   right( new KDNode< int >() );
    const size_t                             leafIndex       = 3;

    KDNode< int > dummyNode( hyperplaneIndex,
                             hyperplaneValue,
                             left,
                             right,
                             leafIndex );

    ASSERT_EQ( dummyNode.hyperplaneIndex()                   , hyperplaneIndex );
    ASSERT_EQ( dummyNode.value()                             , hyperplaneValue );
    ASSERT_EQ( dummyNode.left()                              , left );
    ASSERT_EQ( dummyNode.right()                             , right );
    ASSERT_EQ( dummyNode.leafIndex()                         , leafIndex );

    std::cout << dummyNode << std::endl;
}

} // namespace