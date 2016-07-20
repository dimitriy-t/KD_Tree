#include <iostream>
#include <fstream>
#include <cstdio>

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
            const Types::Indexes& indexes ) const
    {
        return KDTree< int >::chooseBestSplit( indexes );
    }

    std::shared_ptr< KDNode< int > > root()
    {
        return m_root;
    }

    TestPoints points()
    {
        return m_points;
    }
};

const std::string testFile = "really_long_and_unique_test_file_name_42.txt";

class TestFileGuard
{
public:
    TestFileGuard( const std::string& testFileName )
    : m_testFileName( testFileName )
    {
        // nothing to do here
    }

    ~TestFileGuard()
    {
        std::remove( m_testFileName.c_str() );
    }

private:
    std::string   m_testFileName;
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
        if ( temp <= smallestDist )
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
    points.push_back( p1 );
    points.push_back( p2 );
    points.push_back( p3 );

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
    sanityPoints.push_back( p1 );

    TestHyperplane emptyHyperplane;

    TestKDTree sanityTree( sanityPoints );

    std::cout << sanityTree << std::endl;
    std::cout << *sanityTree.root() << std::endl;

    ASSERT_TRUE( sanityTree.root()->isLeaf() );
    ASSERT_EQ  ( sanityTree.root()->leafPointIndex(), 0u );

    //ASSERT_EQ  ( sanityTree.root()->leafPoint()     , p1 );

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
    sanityPoints.push_back( p1 );
    sanityPoints.push_back( p2 );

    TestKDTree sanityTree( sanityPoints );

    std::cout << sanityTree << std::endl;

    ASSERT_FALSE( sanityTree.root()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->hyperplane(), sanityHyperplane );

    ASSERT_TRUE(  sanityTree.root()->left()->isLeaf()  );
    ASSERT_TRUE(  sanityTree.root()->right()->isLeaf() );

    ASSERT_EQ(    sanityTree.root()->left()->leafPointIndex() , 0u );
    ASSERT_EQ(    sanityTree.root()->right()->leafPointIndex(), 1u );

    //ASSERT_EQ(    sanityTree.root()->left()->leafPoint()      , p1 );
    //ASSERT_EQ(    sanityTree.root()->right()->leafPoint()     , p2 );

    ASSERT_EQ(    sanityTree.points(), sanityPoints );
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
    sanityPoints.push_back( p1 );
    sanityPoints.push_back( p2 );
    sanityPoints.push_back( p3 );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    ASSERT_FALSE( sanityTree.root()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->hyperplane(), sanityHyperplane1 );

    // Left part must be a leaf on "-2"
    ASSERT_TRUE(  sanityTree.root()->left()->isLeaf() );
    ASSERT_EQ(    sanityTree.root()->left()->leafPointIndex(), 0u );

    //ASSERT_EQ(    sanityTree.root()->left()->leafPoint(), p1 );

    // Right part must not be a leaf and contain "0", "1"
    ASSERT_FALSE( sanityTree.root()->right()->isLeaf() );
    ASSERT_EQ(    sanityTree.root()->right()->hyperplane(),
                  sanityHyperplane2 );

    ASSERT_EQ(    sanityTree.root()->right()->left()->leafPointIndex() , 1u );
    ASSERT_EQ(    sanityTree.root()->right()->right()->leafPointIndex(), 2u );

//    ASSERT_EQ(    sanityTree.root()->right()->left()->leafPoint() , p2 );
//    ASSERT_EQ(    sanityTree.root()->right()->right()->leafPoint(), p3 );
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
    sanityPoints.push_back( upperLeft );
    sanityPoints.push_back( bottomLeft );
    sanityPoints.push_back( upperRight );
    sanityPoints.push_back( bottomRight );

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


    ASSERT_EQ( sanityTree.root()->left()->left()->leafPointIndex(),  1u );
    ASSERT_EQ( sanityTree.root()->left()->right()->leafPointIndex(), 0u );

//    ASSERT_EQ( sanityTree.root()->left()->left()->leafPoint(),  bottomLeft );
//    ASSERT_EQ( sanityTree.root()->left()->right()->leafPoint(), upperLeft );

    // Left node must partition on x due to higher [ -4; 4 ] spread
    ASSERT_FALSE( sanityTree.root()->right()->isLeaf() );
    ASSERT_TRUE(  sanityTree.root()->right()->left()  != nullptr );
    ASSERT_TRUE(  sanityTree.root()->right()->right() != nullptr );
    ASSERT_EQ(    sanityTree.root()->right()->hyperplane(),
                      rightHyperplane );

    ASSERT_EQ( sanityTree.root()->right()->left()->leafPointIndex(), 3u );
    ASSERT_EQ( sanityTree.root()->right()->right()->leafPointIndex(),2u );

//    ASSERT_EQ( sanityTree.root()->right()->left()->leafPoint(), bottomRight );
//    ASSERT_EQ( sanityTree.root()->right()->right()->leafPoint(), upperRight );
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
    sanityData.push_back( p1 );

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
    sanityData.push_back( p1 );
    sanityData.push_back( p2 );

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
    sanityPoints.push_back( p1 );
    sanityPoints.push_back( p2 );
    sanityPoints.push_back( p3 );

    TestKDTree sanityTree( sanityPoints );
    std::cout << sanityTree << std::endl;

    TestPoint pointOfInterest0;
    pointOfInterest0.push_back( -100 ); // x
    pointOfInterest0.push_back(  0 );  // y
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
    pointOfInterest3.push_back(  0 ); // y
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest3 ) );

    TestPoint pointOfInterest4;
    pointOfInterest4.push_back( 0 ); // x
    pointOfInterest4.push_back( 0 ); // y
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest4 ) );

    TestPoint pointOfInterest5;
    pointOfInterest5.push_back( 1 ); // x
    pointOfInterest5.push_back( 0 ); // y
    ASSERT_EQ( p2, sanityTree.nearestPoint( pointOfInterest5 ) );

    TestPoint pointOfInterest6;
    pointOfInterest6.push_back( 3 ); // x
    pointOfInterest6.push_back( 0 ); // y
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest6 ) );

    TestPoint pointOfInterest7;
    pointOfInterest7.push_back( 5 ); // x
    pointOfInterest7.push_back( 0 ); // y
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest7 ) );

    TestPoint pointOfInterest8;
    pointOfInterest8.push_back( 100 ); // x
    pointOfInterest8.push_back( 0 );   // y
    ASSERT_EQ( p3, sanityTree.nearestPoint( pointOfInterest8 ) );
}

TEST( KDTree, StressTest )
{
    TestPoint upperLeft;
    upperLeft.push_back( -11 ); // x
    upperLeft.push_back(  5 ); // y

    TestPoint bottomLeft;
    bottomLeft.push_back( -10 ); // x
    bottomLeft.push_back( -6 ); // y

    TestPoint upperRight;
    upperRight.push_back( 11 ); // x
    upperRight.push_back( 6 ); // y

    TestPoint bottomRight;
    bottomRight.push_back(  12 ); // x
    bottomRight.push_back( -7 ); // y

    TestPoints sanityPoints;
    sanityPoints.push_back( upperLeft );
    sanityPoints.push_back( bottomLeft );
    sanityPoints.push_back( upperRight );
    sanityPoints.push_back( bottomRight );

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
        //std::cout << "Checking " << ( *it ) << std::endl;

        TestPoint bruteForcePoint = bruteForceClosest( sanityPoints, ( *it ) );
        TestPoint treePoint       = sanityTree.nearestPoint( *it );

        ASSERT_EQ( bruteForcePoint, treePoint );
    }
}

TEST( KDTREE, SerializeEmptyTreeTest )
{
    TestFileGuard guard( testFile );
    TestPoints treePoints;

    TestKDTree sampleTree( treePoints );
    std::cout << sampleTree << std::endl;

    ASSERT_TRUE( sampleTree.serialize( testFile ) );

    std::ifstream treeData( testFile );
    ASSERT_TRUE( treeData.is_open() );

    {
        const std::string expected1 = "0";
        std::string serialized1;
        ASSERT_TRUE( getline( treeData, serialized1 ) );
        ASSERT_EQ( expected1, serialized1 );
    }
    {
        std::string serialized2;
        ASSERT_TRUE( getline( treeData, serialized2 ) );
        ASSERT_EQ( Constants::KDTREE_EMPTY_MARKER, serialized2 );
    }

    {
        std::string serialized;
        ASSERT_FALSE( getline( treeData, serialized ) );
    }
}

TEST( KDTREE, SerializeTreeOnOneNodeTest )
{
    TestFileGuard guard( testFile );
    TestPoints treePoints;
    {
        TestPoint p;
        p.push_back( 1 );
        treePoints.push_back( p );
    }

    TestKDTree sampleTree( treePoints );
    std::cout << sampleTree << std::endl;

    ASSERT_TRUE( sampleTree.serialize( testFile ) );

    std::ifstream treeData( testFile );
    ASSERT_TRUE( treeData.is_open() );

    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "0";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }



    {
        std::string serialized;
        ASSERT_FALSE( getline( treeData, serialized ) );
    }
}

TEST( KDTREE, SerializeTreeOnTwoNodesTest )
{
    TestFileGuard guard( testFile );
    TestPoints treePoints;
    {
        TestPoint p;
        p.push_back( 1 );
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back( 2 );
        treePoints.push_back( p );
    }

    TestKDTree sampleTree( treePoints );
    std::cout << sampleTree << std::endl;

    ASSERT_TRUE( sampleTree.serialize( testFile ) );

    std::ifstream treeData( testFile );
    ASSERT_TRUE( treeData.is_open() );

    {
        const std::string expected = "2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "0 2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "0";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }



    {
        std::string serialized;
        ASSERT_FALSE( getline( treeData, serialized ) );
    }
}

TEST( KDTREE, SerializeTreeOnThreeNodesTest )
{
    TestFileGuard guard( testFile );
    TestPoints treePoints;
    {
        TestPoint p;
        p.push_back( 1 );
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back( 2 );
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back( 3 );
        treePoints.push_back( p );
    }

    TestKDTree sampleTree( treePoints );
    std::cout << sampleTree << std::endl;

    ASSERT_TRUE( sampleTree.serialize( testFile ) );

    std::ifstream treeData( testFile );
    ASSERT_TRUE( treeData.is_open() );

    {
        const std::string expected = "3";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "3";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "0 2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "0";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "0 3";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }




    {
        std::string serialized;
        ASSERT_FALSE( getline( treeData, serialized ) );
    }
}

TEST( KDTREE, SerializeTreeOnFourNodesTest )
{
    TestFileGuard guard( testFile );
    TestPoints treePoints;
    {
        TestPoint p;
        p.push_back( -6 ); // x
        p.push_back(  2 ); // x
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back( -6 ); // x
        p.push_back( -2 ); // x
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back( 6 ); // x
        p.push_back( 4 ); // x
        treePoints.push_back( p );
    }
    {
        TestPoint p;
        p.push_back(  6 ); // x
        p.push_back( -4 ); // x
        treePoints.push_back( p );
    }

    TestKDTree sampleTree( treePoints );
    std::cout << sampleTree << std::endl;

    ASSERT_TRUE( sampleTree.serialize( testFile ) );

    std::ifstream treeData( testFile );
    ASSERT_TRUE( treeData.is_open() );

    {
        const std::string expected = "4";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "-6,2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "-6,-2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "6,4";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        const std::string expected = "6,-4";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }

    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "0 6";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "1 2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "1";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "0";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_HYPERPLANE_MARKER, serialized );
    }
    {
        const std::string expected = "1 4";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "3";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }
    {
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( Constants::KDTREE_LEAF_MARKER, serialized );
    }
    {
        const std::string expected = "2";
        std::string serialized;
        ASSERT_TRUE( getline( treeData, serialized ) );
        ASSERT_EQ( expected, serialized );
    }



    {
    std::string serialized;
    ASSERT_FALSE( getline( treeData, serialized ) );
    }
}

//TEST( KDTREE, SerializeDeserializeEquivalenceTest )
//{
 //   TestFileGuard guard( testFile );
//
//    TestPoints treePoints;
//    {
//        TestPoint p;
//        p.push_back( 1 );
//        treePoints.push_back( p );
//    }
//    {
//        TestPoint p;
//        p.push_back( 2 );
//        treePoints.push_back( p );
//    }
//    {
//        TestPoint p;
//        p.push_back( 3 );
//        treePoints.push_back( p );
//    }
//
//    TestKDTree sampleTree( treePoints );
//    std::cout << sampleTree << std::endl;
//
//    ASSERT_TRUE( sampleTree.serialize( testFile ) );
//    TestKDTree deserializedTree;
//
//    ASSERT_TRUE( deserializedTree.deserialize( testFile ) );
//    std::cout << deserializedTree << std::endl;
//
//    ASSERT_EQ( sampleTree, deserializedTree );
//}

} // namespace
