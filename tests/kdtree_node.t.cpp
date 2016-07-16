#include "gtest/gtest.h"

#include "kdtree_node.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//TEST( KDNode, TestZero )
//{
//    // initial object
//    KDNode< int > zero;
//
//    ASSERT_TRUE( zero == zero );
//    ASSERT_TRUE( !( zero != zero ) );
//    ASSERT_TRUE( zero.equals( zero ) );
//
//    // Empty configs must be equivalent
//    KDNode< int > zero2;
//
//    ASSERT_TRUE( zero == zero2 );
//    ASSERT_TRUE( !( zero != zero2 ) );
//    ASSERT_TRUE( zero.equals( zero2 ) );
//
//    // copy of initial object
//    KDNode< int > zeroCopy( zero );
//    ASSERT_TRUE( zero == zeroCopy );
//    ASSERT_TRUE( !( zero != zeroCopy ) );
//    ASSERT_TRUE( zero.equals( zeroCopy ) );
//
//    // assign of initial object
//    KDNode< int > zeroAssign;
//    zeroAssign = zero;
//    ASSERT_TRUE( zero == zeroAssign );
//    ASSERT_TRUE( !( zero != zeroAssign ) );
//    ASSERT_TRUE( zero.equals( zeroAssign ) );
//}

//TEST( KDNode, TestUninitializedState )
//{
//    KDNode< int > dummyNode;
//    // Because horizontally aligned code blocks are just better!
//    ASSERT_EQ( dummyNode.minNumThreads()                     , 0 );
//}

//TEST( KDNode, Sanity )
//{
//    KDNode< int > dummyNode;
//
//    ASSERT_TRUE( dummyNode.init( "test_data/validKDNode< int >.cfg" ) );
//
//    ASSERT_EQ( dummyNode.minNumThreads()                     , 2 );
//    ASSERT_EQ( dummyNode.maxNumThreads()                     , 2 );
//    ASSERT_EQ( dummyNode.maxIdleTime()                       , 100500 );
//    ASSERT_EQ( dummyNode.maxBatchSize()                      , 10 );
//    ASSERT_EQ( dummyNode.queueSizeWarningThreshold()         , 5000U );
//    ASSERT_EQ( dummyNode.queueSizeWarningTimeoutInSeconds()  , 10U );
//    ASSERT_EQ( dummyNode.queueSizeAlarmThreshold()           , 10000U );
//    ASSERT_EQ( dummyNode.queueSizeAlarmTimeoutInSeconds()    , 10U );
//    ASSERT_EQ( dummyNode.overseerSamplingInMs()              , 1000000U );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxAppName()     ,
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_APP_NAME );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxServiceName() ,
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_LNMUPCR_SERVICE_NAME );
//    ASSERT_EQ( dummyNode.redisAddress().portmuxInstanceName(),
//            Defaults::MGBUTRG_PORTMUX_DEFAULT_INSTANCE_NAME );
//
//    std::cout << dummyNode << std::endl;
//}

//TEST( KDNode, TestPrint )
//{
//    KDNode< int > dummyNode;
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
//    ASSERT_TRUE( dummyNode.init( "test_data/validKDNode< int >.cfg" ) );
//
//    std::cout << dummyNode << std::endl;
//}

} // namespace