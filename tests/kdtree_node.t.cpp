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
    KDNode< int >        dummyNode;
    KDHyperplane< int >  dummyHyperplane;

    ASSERT_EQ( dummyNode.hyperplane(),   dummyHyperplane );
    ASSERT_EQ( dummyNode.left(),         nullptr );
    ASSERT_EQ( dummyNode.left(),         nullptr );
    ASSERT_EQ( dummyNode.leafPointPtr(), nullptr );
}

TEST( KDNode, SanityNonLeaf )
{
    KDHyperplane< int >                           hyperplane( 1u, 2 );
    const std::shared_ptr< KDNode< int > >        left( new KDNode< int >() );
    const std::shared_ptr< KDNode< int > >        right( new KDNode< int >() );
    const std::shared_ptr< Types::Point< int > >  leafPointPtr(
            new Types::Point< int >() );

    KDNode< int > dummyNode( hyperplane,
                             left,
                             right );

    ASSERT_EQ( dummyNode.hyperplane()   , hyperplane );
    ASSERT_EQ( dummyNode.left()         , left );
    ASSERT_EQ( dummyNode.right()        , right );
    ASSERT_EQ( dummyNode.leafPointPtr() , leafPointPtr.get() );

    std::cout << dummyNode << std::endl;

    KDNode< int > dummyNode2 = dummyNode;
    ASSERT_EQ( dummyNode2.hyperplane()   , hyperplane );
    ASSERT_EQ( dummyNode2.left()         , left );
    ASSERT_EQ( dummyNode2.right()        , right );
    ASSERT_EQ( dummyNode2.leafPointPtr() , leafPointPtr.get() );

    std::cout << dummyNode2 << std::endl;

    KDNode< int > dummyNode3 = dummyNode;
    ASSERT_EQ( dummyNode3.hyperplane()   , hyperplane );
    ASSERT_EQ( dummyNode3.left()         , left );
    ASSERT_EQ( dummyNode3.right()        , right );
    ASSERT_EQ( dummyNode3.leafPointPtr() , leafPointPtr.get() );

    std::cout << dummyNode2 << std::endl;

    ASSERT_EQ( dummyNode, dummyNode2 );
    ASSERT_EQ( dummyNode, dummyNode3 );
    ASSERT_EQ( dummyNode2, dummyNode3 );
}


TEST( KDNode, SanityLeaf )
{
    std::cout << "Implement me!" << std::endl;
    ASSERT_TRUE( false );

//    KDHyperplane< int >                           hyperplane( 1u, 2 );
//    const std::shared_ptr< KDNode< int > >        left( new KDNode< int >() );
//    const std::shared_ptr< KDNode< int > >        right( new KDNode< int >() );
//    const std::shared_ptr< Types::Point< int > >  leafPointPtr(
//            new Types::Point< int >() );
//
//    KDNode< int > dummyNode( hyperplane,
//                             left,
//                             right );
//
//    ASSERT_EQ( dummyNode.hyperplane()   , hyperplane );
//    ASSERT_EQ( dummyNode.left()         , left );
//    ASSERT_EQ( dummyNode.right()        , right );
//    ASSERT_EQ( dummyNode.leafPointPtr() , leafPointPtr.get() );
//
//    std::cout << dummyNode << std::endl;
//
//    KDNode< int > dummyNode2 = dummyNode;
//    ASSERT_EQ( dummyNode2.hyperplane()   , hyperplane );
//    ASSERT_EQ( dummyNode2.left()         , left );
//    ASSERT_EQ( dummyNode2.right()        , right );
//    ASSERT_EQ( dummyNode2.leafPointPtr() , leafPointPtr.get() );
//
//    std::cout << dummyNode2 << std::endl;
//
//    KDNode< int > dummyNode3 = dummyNode;
//    ASSERT_EQ( dummyNode3.hyperplane()   , hyperplane );
//    ASSERT_EQ( dummyNode3.left()         , left );
//    ASSERT_EQ( dummyNode3.right()        , right );
//    ASSERT_EQ( dummyNode3.leafPointPtr() , leafPointPtr.get() );
//
//    std::cout << dummyNode2 << std::endl;
//
//    ASSERT_EQ( dummyNode, dummyNode2 );
//    ASSERT_EQ( dummyNode, dummyNode3 );
//    ASSERT_EQ( dummyNode2, dummyNode3 );
}

} // namespace