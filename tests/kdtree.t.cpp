#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// LOCAL TYPES AND DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

typedef Types::Point< int >   TestPoint;
typedef Types::Points< int >  TestPoints;
typedef KDHyperplane< int >   TestHyperplane;

class TestKDTree : public KDTree< int >
{
public:
    TestKDTree()
            : KDTree< int >()
    {
        // nothing to do here
    }

    TestKDTree( const TestPoints& testPoints )
            : KDTree< int >( testPoints )
    {
        // nothing to do here
    }

    virtual const TestHyperplane chooseBestSplit(
            const TestPoints& points ) const
    {
        return KDTree< int >::chooseBestSplit( points );
    }

    std::shared_ptr< KDNode< int > > root()
    {
        return m_root;
    }
};


//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( KDTree, TestZero )
{
    // initial object
    TestKDTree zero;

    ASSERT_TRUE( zero == zero );
    ASSERT_TRUE( !( zero != zero ) );
    ASSERT_TRUE( zero.equals( zero ) );

    // Empty configs must be equivalent
    TestKDTree zero2;

    ASSERT_TRUE( zero == zero2 );
    ASSERT_TRUE( !( zero != zero2 ) );
    ASSERT_TRUE( zero.equals( zero2 ) );

    // copy of initial object
    TestKDTree zeroCopy( zero );

    ASSERT_TRUE( zero == zeroCopy );
    ASSERT_TRUE( !( zero != zeroCopy ) );
    ASSERT_TRUE( zero.equals( zeroCopy ) );

    // assign of initial object
    TestKDTree zeroAssign;
    zeroAssign = zero;
    ASSERT_TRUE( zero == zeroAssign );
    ASSERT_TRUE( !( zero != zeroAssign ) );
    ASSERT_TRUE( zero.equals( zeroAssign ) );
}

TEST( KDTree, TestUninitializedState )
{
    TestKDTree dummyTree;
    TestPoints dummyPoints;

    ASSERT_EQ( dummyTree.root(),   nullptr );
    ASSERT_EQ( dummyTree.points(), dummyPoints );
    ASSERT_EQ( dummyTree.type(),   Defaults::KDTREE_SIMPLE_VARIETY );
}

//TEST( KDTree, TestPrint )
//{
//    std::cout << "Implement me!" << std::endl;
//    ASSERT_TRUE( false );
//    TestKDTree dummyNode;
//
//    ASSERT_EQ( dummyNode.minNumThreads()                     , 0 );
//    ASSERT_EQ( dummyNode.maxNumThreads()                     , 0 );
//    ASSERT_EQ( dummyNode.maxIdleTime()                       , 0 );
//    ASSERT_EQ( dummyNode.maxBatchSize()                      , 0 );
//    ASSERT_EQ( dummyNode.queueSizeWarningThreshold()         , 0U );
//    ASSERT_EQ( dummyNode.queueSizeWarningTimeoutInSeconds()  , 0U );
//    ASSERT_EQ( dummyNode.queueSizeAlarmThreshold()           , 0U );
//    ASSERT_EQ( dummyNode.queueSizeAlarmTimeoutInSeconds()    , 0U );
//    ASSERT_EQ( dummyNode.overseerSamplingInMs()              , 0U );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxAppName()     ,
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_UNINIT_APP_NAME );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxServiceName() ,
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_UNINIT_SERVICE_NAME );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxInstanceName(),
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_UNINIT_INSTANCE_NAME );
//
//    ASSERT_TRUE( dummyNode.init( "test_data/validTestKDTree.cfg" ) );
//
//    std::cout << dummyNode << std::endl;
//}

TEST( KDTree, Sanity )
{
    TestPoint p1;
    p1.push_back( 1 );
    p1.push_back( 2 );
    p1.push_back( 3 );

    TestPoint p2;
    p2.push_back( 4 );
    p2.push_back( 5 );
    p2.push_back( 6 );

    TestPoint p3;
    p3.push_back( 6 );
    p3.push_back( 7 );
    p3.push_back( 8 );

    TestPoints sanityData;
    sanityData.insert( p1 );
    sanityData.insert( p2 );
    sanityData.insert( p3 );

    TestKDTree sanityTree( sanityData  );

    ASSERT_EQ( sanityData, sanityTree.points() );
}

} // namespace