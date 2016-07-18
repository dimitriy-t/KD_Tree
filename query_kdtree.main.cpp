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
        while ( line.length() != pos )
        {
            float value = std::stof( line, &pos );
            line = line.substr( pos + 1u );

            treePoint.push_back( value );
        }

        treePoints.insert( treePoint );
    }
    treeData.close();

    KDTree< float > tree( treePoints );
    std::cout << tree << std::endl;

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
        while ( line.length() != pos )
        {
            float value = std::stof( line, &pos );
            line = line.substr( pos + 1u );

            queryPoint.push_back( value );
        }

        Types::Point< float > brutePoint = bruteForceClosest( treePoints, queryPoint );
        Types::Point< float > treePoint  = tree.nearestPoint( queryPoint );

        if ( brutePoint != treePoint )
        {
            ++numMismatches;
            std::cout << "Houston, we have a problem!" << std::endl;
            std::cout << "    query = " << queryPoint  << std::endl;
            std::cout << "    brute = " << brutePoint  << std::endl;
            std::cout << "    tree = "  << treePoint   << std::endl;
        }
    }

    queryData.close();

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