#include "gtest/gtest.h"

#include "kdtree_types.h"
#include "kdtree.h"
#include "kdtree_utils.h"

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

TestPoint bruteForceClosest( const TestPoints& points,
                             const TestPoint& pointOfInterest )
{
    // Sanity
    if ( !points.size() )
    {
        return TestPoint();
    }

    typename TestPoints::const_iterator it = points.cbegin();
    TestPoint closestSoFar = ( *it );
    double smallestDist = Utils::distance< int >( pointOfInterest, ( *it ) );
    ++it;

    for (;it != points.cend(); ++it )
    {
        const double temp = Utils::distance< int >( pointOfInterest, ( *it ) );
        if ( temp < smallestDist )
        {
            smallestDist = temp;
            closestSoFar = ( *it );
        }
    }

    return closestSoFar;
}

//////////////////////////////////////////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

TEST( Helpers, TestBruteForceClosest )
{
    TestPoint p1;
    p1.push_back( -1 ); // x
    p1.push_back(  1 ); // y

    TestPoint p2;
    p2.push_back( 0 ); // x
    p2.push_back( 1 ); // y

    TestPoint p3;
    p3.push_back( 1 ); // x
    p3.push_back( 1 ); // y

    TestPoints points;
    points.insert( p1 );
    points.insert( p2 );
    points.insert( p3 );

    TestPoint pOfInterest;
    pOfInterest.push_back( 0 ); // x
    pOfInterest.push_back( 0 ); // y

    ASSERT_EQ( bruteForceClosest( points, pOfInterest ), p2 );
}


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
    ASSERT_EQ( dummyTree.type(),   Constants::KDTREE_SIMPLE_VARIETY );

    std::cout << dummyTree << std::endl;
}

TEST( KDTree, TreeOnOneNode )
{
    TestPoint p1;
    p1.push_back( 1 );
    p1.push_back( 2 );
    p1.push_back( 3 );

    TestPoints sanityPoints;
    sanityPoints.insert( p1 );

    TestHyperplane emptyHyperplane;

    TestKDTree sanityTree( sanityPoints );

    std::cout << sanityTree << std::endl;
    std::cout << *sanityTree.root() << std::endl;

    ASSERT_TRUE( sanityTree.root()->isLeaf() );
    ASSERT_EQ  ( sanityTree.root()->leafPoint() , p1 );
    ASSERT_EQ  ( sanityTree.points()            , sanityPoints );
    ASSERT_EQ  ( sanityTree.root()->hyperplane(), emptyHyperplane );
    ASSERT_EQ  ( sanityTree.root()->left()      , nullptr );
    ASSERT_EQ  ( sanityTree.root()->right()     , nullptr );
}

TEST( KDTree, TreeOnTwoNodes )
{
    TestHyperplane sanityHyperplane( 0u, 1 );

    TestPoint p1;
    p1.push_back( -1 );

    TestPoint p2;
    p2.push_back( 1 );

    TestPoints sanityPoints;
    sanityPoints.insert( p1 );
    sanityPoints.insert( p2 );

    TestKDTree sanityTree( sanityPoints );

    std::cout << sanityTree << std::endl;

    ASSERT_FALSE( sanityTree.root()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->hyperplane(), sanityHyperplane );

    ASSERT_TRUE(  sanityTree.root()->left()->isLeaf()  );
    ASSERT_TRUE(  sanityTree.root()->right()->isLeaf() );

    ASSERT_EQ(    sanityTree.root()->left()->leafPoint() , p1 );
    ASSERT_EQ(    sanityTree.root()->right()->leafPoint(), p2 );

    ASSERT_EQ(    sanityTree.points()            , sanityPoints );
}

TEST( KDTree, TreeOnThreeNodes )
{
    TestHyperplane sanityHyperplane1( 0u, 0 );
    TestHyperplane sanityHyperplane2( 0u, 1 );

    TestPoint p1;
    p1.push_back( -3 );

    TestPoint p2;
    p2.push_back( 0 );

    TestPoint p3;
    p3.push_back( 1 );

    TestPoints sanityPoints;
    sanityPoints.insert( p1 );
    sanityPoints.insert( p2 );
    sanityPoints.insert( p3 );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    ASSERT_FALSE( sanityTree.root()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->hyperplane(), sanityHyperplane1 );

    // Left part must be a leaf on "-2"
    ASSERT_TRUE(  sanityTree.root()->left()->isLeaf() );
    ASSERT_EQ(    sanityTree.root()->left()->leafPoint(), p1 );

    // Right part must not be a leaf and contain "0", "1"
    ASSERT_FALSE( sanityTree.root()->right()->isLeaf() );
    ASSERT_EQ(    sanityTree.root()->right()->hyperplane(),
                  sanityHyperplane2 );

    ASSERT_EQ(    sanityTree.root()->right()->left()->leafPoint(),  p2 );
    ASSERT_EQ(    sanityTree.root()->right()->right()->leafPoint(), p3 );
}

TEST( KDTree, TreeOnFourNodes )
{
    TestHyperplane centerHyperplane( 0u, 6 );
    TestHyperplane leftHyperplane(   1u, 2 );
    TestHyperplane rightHyperplane(  1u, 4 );

    TestPoint upperLeft;
    upperLeft.push_back( -6 ); // x
    upperLeft.push_back(  2 ); // y

    TestPoint bottomLeft;
    bottomLeft.push_back( -6 ); // x
    bottomLeft.push_back( -2 ); // y

    TestPoint upperRight;
    upperRight.push_back( 6 ); // x
    upperRight.push_back( 4 ); // y

    TestPoint bottomRight;
    bottomRight.push_back(  6 ); // x
    bottomRight.push_back( -4 ); // y

    TestPoints sanityPoints;
    sanityPoints.insert( upperLeft );
    sanityPoints.insert( bottomLeft );
    sanityPoints.insert( upperRight );
    sanityPoints.insert( bottomRight );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    // First node must partition on x due to higher [ -6; 6 ] spread
    ASSERT_FALSE( sanityTree.root()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->hyperplane(), centerHyperplane );

    // Left node must partition on x due to higher [ -2; 2 ] spread
    ASSERT_FALSE( sanityTree.root()->left()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->left()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->left()->hyperplane(),
                      leftHyperplane );
    ASSERT_EQ(    sanityTree.root()->left()->left()->leafPoint(),
                      bottomLeft  );
    ASSERT_EQ(    sanityTree.root()->left()->right()->leafPoint(),
                      upperLeft   );

    // Left node must partition on x due to higher [ -4; 4 ] spread
    ASSERT_FALSE( sanityTree.root()->right()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->right()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->right()->hyperplane(),
                      rightHyperplane );
    ASSERT_EQ(    sanityTree.root()->right()->left()->leafPoint(),
                      bottomRight  );
    ASSERT_EQ(    sanityTree.root()->right()->right()->leafPoint(),
                      upperRight   );
}

TEST( KDTree, FarilyRaindomSanity )
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
    std::cout << sanityTree << std::endl;

    ASSERT_EQ( sanityData, sanityTree.points() );
}

TEST( KDTree, SearchOnEmptyTree )
{
    TestKDTree sanityTree;

    TestPoint pointOfInterest;
    pointOfInterest.push_back( 0 );

    ASSERT_EQ( TestPoint(), sanityTree.nearestPoint( pointOfInterest ) );
}

TEST( KDTree, SearchTreeOnOneNode )
{
    TestPoint p1;
    p1.push_back( 0 );

    TestPoints sanityData;
    sanityData.insert( p1 );

    TestKDTree sanityTree( sanityData  );
    std::cout << sanityTree << std::endl;

    TestPoint pointOfInterest;
    pointOfInterest.push_back( 1 );

    ASSERT_EQ( p1, sanityTree.nearestPoint( pointOfInterest ) );
}

TEST( KDTree, SearchTreeOnTwoNodes )
{
    TestPoint p1;
    p1.push_back( -3 );

    TestPoint p2;
    p2.push_back( 3 );

    TestPoints sanityData;
    sanityData.insert( p1 );
    sanityData.insert( p2 );

    TestKDTree sanityTree( sanityData  );
    std::cout << sanityTree << std::endl;

    TestPoint pointOfInterest;
    pointOfInterest.push_back( 1 );

    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest ) );
}

TEST( KDTree, SearchTreeOnThreeNodes )
{
    TestPoint p1;
    p1.push_back( -3 ); // x
    p1.push_back(  0 ); // y

    TestPoint p2;
    p2.push_back( 0 ); // x
    p2.push_back( 0 ); // y

    TestPoint p3;
    p3.push_back( 4 ); // x
    p3.push_back( 0 ); // y

    TestPoints sanityPoints;
    sanityPoints.insert( p1 );
    sanityPoints.insert( p2 );
    sanityPoints.insert( p3 );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    TestPoint pointOfInterest0;
    pointOfInterest0.push_back( -100 ); // x
    pointOfInterest0.push_back(  0 ); // y
    ASSERT_EQ( p1, sanityTree.nearestPoint( pointOfInterest0 ) );

    TestPoint pointOfInterest1;
    pointOfInterest1.push_back( -5 ); // x
    pointOfInterest1.push_back(  0 ); // y
    ASSERT_EQ( p1, sanityTree.nearestPoint( pointOfInterest1 ) );

    TestPoint pointOfInterest2;
    pointOfInterest2.push_back( -2 ); // x
    pointOfInterest2.push_back(  0 ); // y
    ASSERT_EQ( p1, sanityTree.nearestPoint( pointOfInterest2 ) );

    TestPoint pointOfInterest3;
    pointOfInterest3.push_back( -1 ); // x
    pointOfInterest3.push_back(  0 ); // x
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest3 ) );

    TestPoint pointOfInterest4;
    pointOfInterest4.push_back( 0 ); // x
    pointOfInterest4.push_back( 0 ); // x
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest4 ) );

    TestPoint pointOfInterest5;
    pointOfInterest5.push_back( 1 ); // x
    pointOfInterest5.push_back( 0 ); // x
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest5 ) );

    TestPoint pointOfInterest6;
    pointOfInterest6.push_back( 3 ); // x
    pointOfInterest6.push_back( 0 ); // x
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest6 ) );

    TestPoint pointOfInterest7;
    pointOfInterest7.push_back( 5 ); // x
    pointOfInterest7.push_back( 0 ); // x
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest7 ) );

    TestPoint pointOfInterest8;
    pointOfInterest8.push_back( 100 ); // x
    pointOfInterest8.push_back( 0 ); // x
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest8 ) );
}

TEST( KDTree, StressTest )
{
    TestPoint upperLeft;
    upperLeft.push_back( -10 ); // x
    upperLeft.push_back(  5 ); // y

    TestPoint bottomLeft;
    bottomLeft.push_back( -10 ); // x
    bottomLeft.push_back( -5 ); // y

    TestPoint upperRight;
    upperRight.push_back( 11 ); // x
    upperRight.push_back( 6 ); // y

    TestPoint bottomRight;
    bottomRight.push_back(  11 ); // x
    bottomRight.push_back( -6 ); // y

    TestPoints sanityPoints;
    sanityPoints.insert( upperLeft );
    sanityPoints.insert( bottomLeft );
    sanityPoints.insert( upperRight );
    sanityPoints.insert( bottomRight );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    std::vector< TestPoint > testPoints;
    for ( int x = -15; x < 16; ++x )
    {
        for ( int y = -10; y < 10; ++y )
        {
            TestPoint test;
            test.push_back( x );
            test.push_back( y );
            testPoints.push_back( test );
        }
    }

    for ( typename std::vector< TestPoint >::const_iterator it
              = testPoints.cbegin();
          it < testPoints.cend(); ++it )
    {
        ASSERT_EQ( bruteForceClosest( sanityPoints, ( *it ) ),
                   sanityTree.nearestPoint( *it ) );
    }
}

} // namespace

