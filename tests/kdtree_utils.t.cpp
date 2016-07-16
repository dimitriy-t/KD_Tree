#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree_utils.h"

using namespace datastructures;

namespace {

//////////////////////////////////////////////////////////////////////////////
// LOCAL TYPES AND DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

typedef Types::Point< int >   TestPoint;
typedef Types::Points< int >  TestPoints;

//////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( Utils, MedianValueInAxis )
{
    TestPoints sanityData;
    ASSERT_EQ( Utils::medianValueInAxis< int >( sanityData, 0u ),
            Defaults::KDTREE_EMPTY_SET_MEDIAN  );

    TestPoint p1;
    p1.push_back( 0  );
    p1.push_back( 1  );
    p1.push_back( 12 );

    TestPoint p2;
    p2.push_back( 0  );
    p2.push_back( 1  );
    p2.push_back( 17 );

    TestPoint p3;
    p3.push_back( 0  );
    p3.push_back( 1  );
    p3.push_back( 19  );

    TestPoint p4;
    p4.push_back( 0  );
    p4.push_back( 1  );
    p4.push_back( 22 );

    TestPoint p5;
    p5.push_back( 0 );
    p5.push_back( 1 );
    p5.push_back( 30 );

    sanityData.push_back( p1 );
    sanityData.push_back( p2 );
    sanityData.push_back( p3 );
    sanityData.push_back( p4 );
    sanityData.push_back( p5 );

    ASSERT_EQ( Utils::medianValueInAxis< int >( sanityData, 0u ), 0 );
    ASSERT_EQ( Utils::medianValueInAxis< int >( sanityData, 1u ), 1 );
    ASSERT_EQ( Utils::medianValueInAxis< int >( sanityData, 2u ), 19 );

    ASSERT_EQ( Utils::medianValueInAxis< int >( sanityData, 42u ),
               Defaults::KDTREE_EMPTY_SET_MEDIAN  );
}

TEST( Utils, AxisMinMax )
{
    TestPoints sanityData;
    ASSERT_EQ( Utils::minMaxPerAxis< int >( sanityData ).size(), 0u );

    TestPoint p1;
    p1.push_back( -1 );
    p1.push_back(  0 );
    p1.push_back( -500 );

    TestPoint p2;
    p2.push_back(  0 );
    p2.push_back(  1 );
    p2.push_back(  0 );

    TestPoint p3;
    p3.push_back(  0  );
    p3.push_back(  2  );
    p3.push_back(  13 );

    TestPoint p4;
    p4.push_back(  0 );
    p4.push_back(  3 );
    p4.push_back( 42 );

    TestPoint p5;
    p5.push_back(  1 );
    p5.push_back(  4 );
    p5.push_back( -5 );

    sanityData.push_back( p1 );
    sanityData.push_back( p2 );
    sanityData.push_back( p3 );
    sanityData.push_back( p4 );
    sanityData.push_back( p5 );

    const Types::AxisMinMax< int > sanityRes =
            Utils::minMaxPerAxis< int >( sanityData );

    ASSERT_EQ( sanityRes[ 0u ].first, -1 );
    ASSERT_EQ( sanityRes[ 0u ].second, 1 );

    ASSERT_EQ( sanityRes[ 1u ].first,  0 );
    ASSERT_EQ( sanityRes[ 1u ].second, 4 );

    ASSERT_EQ( sanityRes[ 2u ].first, -500 );
    ASSERT_EQ( sanityRes[ 2u ].second, 42);
}

TEST( Utils, AxisOfHighestVariance )
{
    TestPoints sanityData;
    ASSERT_EQ( Utils::axisOfHighestVariance< int >( sanityData ),
               Defaults::KDTREE_EMPTY_SET_VARIANCE );

    TestPoint p1;
    p1.push_back( -1 );
    p1.push_back(  0 );
    p1.push_back( -500 );

    TestPoint p2;
    p2.push_back(  0 );
    p2.push_back(  1 );
    p2.push_back(  0 );

    TestPoint p3;
    p3.push_back(  0  );
    p3.push_back(  2  );
    p3.push_back(  13 );

    TestPoint p4;
    p4.push_back(  0 );
    p4.push_back(  3 );
    p4.push_back( 42 );

    TestPoint p5;
    p5.push_back(  1 );
    p5.push_back(  4 );
    p5.push_back( -5 );

    sanityData.push_back( p1 );
    sanityData.push_back( p2 );
    sanityData.push_back( p3 );
    sanityData.push_back( p4 );
    sanityData.push_back( p5 );

    ASSERT_EQ( Utils::axisOfHighestVariance< int >( sanityData ), 2u );
}

} // namespace