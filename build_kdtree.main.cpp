#include <iostream>
#include <fstream>
#include <string>

#include "kdtree.h"

using namespace datastructures;

const std::string defaultTreeDataFile = "kdtree.serialized";

//static void printHelp()
//{
//    std::cout << "Usage: query_kdtree tree_file query_file answers_file                      " << std::endl;
//    std::cout << "                                                                           " << std::endl;
//    std::cout << "    Where :                                                                " << std::endl;
//    std::cout << "      tree_file          - path to file produced by successful             " << std::endl;
//    std::cout << "                           invocation of build_kdtree                      " << std::endl;
//    std::cout << "                                                                           " << std::endl;
//    std::cout << "      query_file         - path CSV file containing query points data      " << std::endl;
//    std::cout << "                           as prescribed by the assignment                 " << std::endl;
//    std::cout << "                                                                           " << std::endl;
//    std::cout << "      answers_file       - path CSV file containing answers to queries     " << std::endl;
//    std::cout << "                           specified by query_file against tree specified  " << std::endl;
//    std::cout << "                           by tree_file. Default value is '"
//              << defaultResultsFilename << "'" << std::endl;
//    std::cout << "                           Note that all contents of an existing file will " << std::endl;
//    std::cout << "                           be erased.                                      " << std::endl;
//}
//
//static bool validateInputs( int argc, char *argv[] )
//{
//    if ( argc < 3 )
//    {
//        return false;
//    }
//
//    return true;
//}

// locations :
//     tree data  - "data/sample_data.csv"
//     query data - "data/query_data.csv"

int main( int argc, char *argv[] )
{
    std::cout << "empty for now" << std::endl;
//    if ( !validateInputs( argc, argv ) )
//    {
//        printHelp();
//        return 1;
//    }
//
//    const std::string treeFileName = argv[ 1 ];
//
//    KDTree< float > tree;
//
//    if ( !tree.deserialize( treeFileName  ) )
//    {
//        printHelp();
//        return 1;
//    }
//
//    std::cout << tree << std::endl;
//
//    const std::string queryFileName = argv[ 2 ];
//
//    std::ifstream queryData( queryFileName );
//
//    if ( !queryData.is_open() )
//    {
//        std::cout << "query_kdtree is unable to open '"
//                  << queryFileName << "' for reading"
//                  << std::endl;
//        return 1;
//    }
//
//    std::string resultsFilename;
//
//    if ( 3 == argc )
//    {
//        resultsFilename = defaultResultsFilename;
//    }
//    else
//    {
//        resultsFilename = argv[ 3 ];
//    }
//
//    std::fstream results;
//    results.open( resultsFilename, std::fstream::out | std::fstream::trunc );
//
//    int numQueriesProcessed = 0;
//    std::string line;
//    while ( getline ( queryData, line ) )
//    {
//        Types::Point< float > queryPoint;
//
//        size_t pos = 0;
//        while ( line.length() != pos )
//        {
//            float value = std::stof( line, &pos );
//            line = line.substr( pos + 1u );
//
//            queryPoint.push_back( value );
//        }
//
//        results << tree.nearestPointIndex( queryPoint ) << '\n';
//        ++numQueriesProcessed;
//    }
//
//    results.close();
//
//    std::cout << "Done" << std::endl;
//    std::cout << "    total number of queries : "
//              << numQueriesProcessed
//              << std::endl;
//    std::cout << "    result written to       : '"
//              << resultsFilename
//              << "'"
//              << std::endl;

    return 0;
}