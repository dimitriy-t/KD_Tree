#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree_constants.h"
#include "kdtree_node.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// LOCAL TYPES AND DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

typedef KDHyperplane< int >   TestHyperplane;
typedef KDNode< int >         TestNode;

//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( KDNode, TestZero )
{
    // initial object
    TestNode zero;

    ASSERT_TRUE( zero == zero );
    ASSERT_TRUE( !( zero != zero ) );
    ASSERT_TRUE( zero.equals( zero ) );

    // Empty configs must be equivalent
    TestNode zero2;

    ASSERT_TRUE( zero == zero2 );
    ASSERT_TRUE( !( zero != zero2 ) );
    ASSERT_TRUE( zero.equals( zero2 ) );

    // copy of initial object
    TestNode zeroCopy( zero );
    ASSERT_TRUE( zero == zeroCopy );
    ASSERT_TRUE( !( zero != zeroCopy ) );
    ASSERT_TRUE( zero.equals( zeroCopy ) );

    // assign of initial object
    TestNode zeroAssign;
    zeroAssign = zero;
    ASSERT_TRUE( zero == zeroAssign );
    ASSERT_TRUE( !( zero != zeroAssign ) );
    ASSERT_TRUE( zero.equals( zeroAssign ) );
}

TEST( KDNode, TestUninitializedState )
{
    TestNode        dummyNode;
    TestHyperplane  dummyHyperplane;

    std::cout << dummyNode << std::endl;

    ASSERT_EQ( dummyNode.hyperplane(),     dummyHyperplane );
    ASSERT_EQ( dummyNode.left(),           nullptr );
    ASSERT_EQ( dummyNode.left(),           nullptr );
    ASSERT_EQ( dummyNode.leafPointIndex(), Constants::KDTREE_ERROR_INDEX );
}

TEST( KDNode, SanityNonLeaf )
{
    TestHyperplane                    hyperplane( 1u, 2 );
    const std::shared_ptr< TestNode>  left( new KDNode< int >() );
    const std::shared_ptr< TestNode>  right( new KDNode< int >() );

    TestNode dummyNode( hyperplane, left, right );

    ASSERT_EQ( dummyNode.hyperplane()    , hyperplane );
    ASSERT_EQ( dummyNode.left()          , left );
    ASSERT_EQ( dummyNode.right()         , right );
    ASSERT_EQ( dummyNode.isLeaf()        , false );
    ASSERT_EQ( dummyNode.leafPointIndex(), Constants::KDTREE_ERROR_INDEX );

    std::cout << dummyNode << std::endl;

    TestNode dummyNode2 = dummyNode;

    ASSERT_EQ( dummyNode2.hyperplane()    , hyperplane );
    ASSERT_EQ( dummyNode2.left()          , left );
    ASSERT_EQ( dummyNode2.right()         , right );
    ASSERT_EQ( dummyNode2.isLeaf()        , false );
    ASSERT_EQ( dummyNode2.leafPointIndex(), Constants::KDTREE_ERROR_INDEX );

    std::cout << dummyNode2 << std::endl;

    TestNode dummyNode3( dummyNode );

    ASSERT_EQ( dummyNode3.hyperplane()    , hyperplane );
    ASSERT_EQ( dummyNode3.left()          , left );
    ASSERT_EQ( dummyNode3.right()         , right );
    ASSERT_EQ( dummyNode3.isLeaf()        , false );
    ASSERT_EQ( dummyNode3.leafPointIndex(), Constants::KDTREE_ERROR_INDEX );

    std::cout << dummyNode2 << std::endl;

    ASSERT_EQ( dummyNode,  dummyNode2 );
    ASSERT_EQ( dummyNode,  dummyNode3 );
    ASSERT_EQ( dummyNode2, dummyNode3 );
}

TEST( KDNode, SanityLeaf )
{
    const size_t   leafPointIndex = 1u;
    TestNode dummyLeafNode( leafPointIndex );
    TestHyperplane emptyHyperplane;

    ASSERT_EQ( dummyLeafNode.hyperplane()    , emptyHyperplane );
    ASSERT_EQ( dummyLeafNode.left()          , nullptr );
    ASSERT_EQ( dummyLeafNode.right()         , nullptr );
    ASSERT_EQ( dummyLeafNode.isLeaf()        , true );
    ASSERT_EQ( dummyLeafNode.leafPointIndex(), leafPointIndex );

    std::cout << dummyLeafNode << std::endl;

    TestNode dummyLeafNode2 = dummyLeafNode;
    ASSERT_EQ( dummyLeafNode2.hyperplane()    , emptyHyperplane );
    ASSERT_EQ( dummyLeafNode2.left()          , nullptr );
    ASSERT_EQ( dummyLeafNode2.right()         , nullptr );
    ASSERT_EQ( dummyLeafNode2.isLeaf()        , true );
    ASSERT_EQ( dummyLeafNode2.leafPointIndex(), leafPointIndex );

    std::cout << dummyLeafNode2 << std::endl;

    TestNode dummyLeafNode3( dummyLeafNode );
    ASSERT_EQ( dummyLeafNode3.hyperplane()    , emptyHyperplane );
    ASSERT_EQ( dummyLeafNode3.left()          , nullptr );
    ASSERT_EQ( dummyLeafNode3.right()         , nullptr );
    ASSERT_EQ( dummyLeafNode3.isLeaf()        , true );
    ASSERT_EQ( dummyLeafNode3.leafPointIndex(), leafPointIndex );

    std::cout << dummyLeafNode3 << std::endl;

    ASSERT_EQ( dummyLeafNode,  dummyLeafNode2 );
    ASSERT_EQ( dummyLeafNode,  dummyLeafNode3 );
    ASSERT_EQ( dummyLeafNode2, dummyLeafNode3 );
}

} // namespace