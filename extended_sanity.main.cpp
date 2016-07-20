#include <iostream>
#include <fstream>
#include <string>

#include "kdtree.h"

using namespace datastructures;

Types::Point< float > bruteForceClosest( const Types::Points< float >& points,
                                         const Types::Point< float >& pointOfInterest )
{
    typename Types::Points< float >::const_iterator it = points.cbegin();

    Types::Point< float > closestSoFar = ( *it );

    double smallestDist = Utils::distance< float >( pointOfInterest, ( *it ) );
    ++it;

    for (;it != points.cend(); ++it )
    {
        const double temp = Utils::distance< float >( pointOfInterest, ( *it ) );
        if ( temp < smallestDist )
        {
            smallestDist = temp;
            closestSoFar = ( *it );
        }
    }

    return closestSoFar;
}

size_t bruteForceClosestIndex( const std::vector< Types::Point< float > >& points,
                               const Types::Point< float >& pointOfInterest )
{
    Types::Point< float > closestSoFar = points[ 0 ];
    double smallestDist = Utils::distance< float >( pointOfInterest, closestSoFar );
    size_t closestIndex = 0;

    for ( size_t i = 1; i < points.size(); ++i )
    {
        const double temp = Utils::distance< float >( pointOfInterest, points[ i ] );
        if ( temp < smallestDist )
        {
            smallestDist = temp;
            closestSoFar = points[ i ];
            closestIndex = i;
        }
    }

    return closestIndex;
}

int main()
{
    const std::string dataFilename = "data/sample_data.csv";
    std::ifstream treeData( dataFilename );

    if ( treeData.is_open() )
    {
        std::cout << "Unable to open '" << dataFilename << "' for reading" << std::endl;
    }

    std::string line;
    Types::Points< float > treePoints;

    while ( getline ( treeData, line ) )
    {
        Types::Point< float > treePoint;

        size_t pos = 0;

        while ( true )
        {
            treePoint.push_back( static_cast< float >( stof( line, &pos ) ) );

            if ( line[ pos ] == ',')
            {
                line = line.substr( pos + 1u );
            }
            else
            {
                break;
            }
        }

        treePoints.push_back( treePoint );
    }
    treeData.close();

    KDTree< float > tree( treePoints );
    std::cout << tree << std::endl;

    Types::Points< float > queryPoints;

    const std::string queryFilename = "data/query_data.csv";
    std::ifstream queryData( queryFilename );

    if ( treeData.is_open() )
    {
        std::cout << "Unable to open '" << dataFilename << "' for reading" << std::endl;
    }

    int numMismatches = 0;
    while ( getline ( queryData, line ) )
    {
        Types::Point< float > queryPoint;

        size_t pos = 0;
        while ( true )
        {
            queryPoint.push_back( static_cast< double >( stof( line, &pos ) ) );

            if ( line[ pos ] == ',')
            {
                line = line.substr( pos + 1u );
            }
            else
            {
                break;
            }
        }

        queryPoints.push_back( queryPoint );
    }

    queryData.close();

    for ( size_t i = 0; i < queryPoints.size(); ++i )
    {
        size_t bruteIndex = bruteForceClosestIndex( treePoints, queryPoints[ i ] );
        size_t treeIndex = tree.nearestPointIndex( queryPoints[ i ] ) ;

        if ( bruteIndex != treeIndex )
        {
            ++numMismatches;
            std::cout << "Houston, we have a problem!" << std::endl;
            std::cout << "    query = " << queryPoints[ i ] << std::endl;
            std::cout << "    brute index = " << bruteIndex << std::endl;
            std::cout << "    tree index = " << treeIndex << std::endl;
        }
    }

    if ( numMismatches )
    {
        std::cout << "Total number of mismatches = " << numMismatches << std::cout;
    }
    else
    {
        std::cout << "They don`t pay you enough!" << std::endl;
    }

    numMismatches = 0;

    for ( size_t i = 0; i < queryPoints.size(); ++i )
    {
        Types::Point< float > brutePoint = bruteForceClosest( treePoints, queryPoints[ i ] );
        Types::Point< float > treePoint  = tree.nearestPoint( queryPoints[ i ] );

        if ( brutePoint != treePoint )
        {
            ++numMismatches;
            std::cout << "Houston, we have a problem!" << std::endl;
            std::cout << "    query = " << queryPoints[ i ] << std::endl;
            std::cout << "    brute = " << brutePoint << std::endl;
            std::cout << "    tree = " << treePoint << std::endl;
        }
    }

    if ( numMismatches )
    {
        std::cout << "Total number of mismatches = " << numMismatches << std::cout;
    }
    else
    {
        std::cout << "They don`t pay you enough!" << std::endl;
    }

    return 0;
}