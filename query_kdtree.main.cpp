#include <iostream>
#include <fstream>
#include <string>

#include "kdtree.h"

using namespace std;
using namespace datastructures;

const string defaultResultsFilename = "results.csv";

static void printHelp()
{
    cout << "Usage: query_kdtree tree_file query_file answers_file                      " << endl;
    cout << "                                                                           " << endl;
    cout << "    Where :                                                                " << endl;
    cout << "      tree_file          - path to file produced by successful             " << endl;
    cout << "                           invocation of build_kdtree                      " << endl;
    cout << "                                                                           " << endl;
    cout << "      query_file         - path CSV file containing query points data      " << endl;
    cout << "                           as prescribed by the assignment                 " << endl;
    cout << "                                                                           " << endl;
    cout << "      answers_file       - path CSV file containing answers to queries     " << endl;
    cout << "                           specified by query_file against tree specified  " << endl;
    cout << "                           by tree_file. Default value is '"
              << defaultResultsFilename << "'" << endl;
    cout << "                           Note that all contents of an existing file will " << endl;
    cout << "                           be erased.                                      " << endl;
}

static bool validateInputs( int argc, char *argv[] )
{
    if ( argc < 3 )
    {
        return false;
    }

    return true;
}

// locations :
//     tree data  - "data/sample_data.csv"
//     query data - "data/query_data.csv"

int main( int argc, char *argv[] )
{
    if ( !validateInputs( argc, argv ) )
    {
        printHelp();
        return 1;
    }

    const string treeFileName = argv[ 1 ];

    KDTree< float > tree;

    if ( !tree.deserialize( treeFileName  ) )
    {
        printHelp();
        return 1;
    }

    cout << tree << endl;

    const string queryFileName = argv[ 2 ];

    ifstream queryData( queryFileName );

    if ( !queryData.is_open() )
    {
        cout << "query_kdtree is unable to open '"
                  << queryFileName << "' for reading"
                  << endl;
        return 1;
    }

    string resultsFilename;

    if ( 3 == argc )
    {
        resultsFilename = defaultResultsFilename;
    }
    else
    {
        resultsFilename = argv[ 3 ];
    }

    fstream results;
    results.open( resultsFilename, fstream::out | fstream::trunc );

    int numQueriesProcessed = 0;
    string line;
    while ( getline ( queryData, line ) )
    {
        Types::Point< float > queryPoint;

        size_t pos = 0;

        while ( true )
        {
            queryPoint.push_back( static_cast< float >( stof( line, &pos ) ) );

            if ( line[ pos ] == ',')
            {
                line = line.substr( pos + 1u );
            }
            else
            {
                break;
            }
        }

        results << tree.nearestPointIndex( queryPoint ) << '\n';
        ++numQueriesProcessed;
    }

    results.close();

    cout << "Done" << endl;
    cout << "    total number of queries : "
              << numQueriesProcessed
              << endl;
    cout << "    result written to       : '"
              << resultsFilename
              << "'"
              << endl;

    return 0;
}