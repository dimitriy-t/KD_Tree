#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree_constants.h"
#include "kdtree_hyperplane.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// LOCAL TYPES AND DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

typedef KDHyperplane< int >   TestHyperplane;

//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( KDHyperplane, TestZero )
{
    // initial object
    TestHyperplane zero;
    
    ASSERT_TRUE( zero == zero );
    ASSERT_TRUE( !( zero != zero ) );
    ASSERT_TRUE( zero.equals( zero ) );
    
    // Empty configs must be equivalent
    TestHyperplane zero2;
    
    ASSERT_TRUE( zero == zero2 );
    ASSERT_TRUE( !( zero != zero2 ) );
    ASSERT_TRUE( zero.equals( zero2 ) );
    
    // copy of initial object
    KDHyperplane< int > zeroCopy( zero );
    ASSERT_TRUE( zero == zeroCopy );
    ASSERT_TRUE( !( zero != zeroCopy ) );
    ASSERT_TRUE( zero.equals( zeroCopy ) );
    
    // assign of initial object
    KDHyperplane< int > zeroAssign;
    zeroAssign = zero;
    ASSERT_TRUE( zero == zeroAssign );
    ASSERT_TRUE( !( zero != zeroAssign ) );
    ASSERT_TRUE( zero.equals( zeroAssign ) );
}

TEST( KDHyperplane, TestUninitializedState )
{
    TestHyperplane dummyHyperplane;

    ASSERT_EQ( dummyHyperplane.hyperplaneIndex(),
            Constants::KDTREE_UNINITIALIZED_HYPERPLANE_INDEX );
    ASSERT_EQ( dummyHyperplane.value(), static_cast< int >(
            Constants::KDTREE_UNINITIALIZED_HYPERPLANE_VALUE ) );
}

TEST( KDHyperplane, Sanity )
{
    const size_t hyperplaneIndex = 1u;
    const int    hyperplaneValue = 2;

    TestHyperplane dummyHyperplane( hyperplaneIndex,
                                         hyperplaneValue );

    ASSERT_EQ( dummyHyperplane.hyperplaneIndex() , hyperplaneIndex );
    ASSERT_EQ( dummyHyperplane.value()           , hyperplaneValue );

    std::cout << dummyHyperplane << std::endl;

    TestHyperplane dummyHyperplane2 = dummyHyperplane;
    ASSERT_EQ( dummyHyperplane2.hyperplaneIndex() , hyperplaneIndex );
    ASSERT_EQ( dummyHyperplane2.value()           , hyperplaneValue );

    std::cout << dummyHyperplane2 << std::endl;

    TestHyperplane dummyHyperplane3( dummyHyperplane );
    ASSERT_EQ( dummyHyperplane3.hyperplaneIndex() , hyperplaneIndex );
    ASSERT_EQ( dummyHyperplane3.value()           , hyperplaneValue );

    std::cout << dummyHyperplane2 << std::endl;

    ASSERT_EQ( dummyHyperplane, dummyHyperplane2 );
    ASSERT_EQ( dummyHyperplane, dummyHyperplane3 );
    ASSERT_EQ( dummyHyperplane2, dummyHyperplane3 );

}

} // namespace