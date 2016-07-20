#include <iostream>
#include <fstream>
#include <string>

#include "kdtree.h"

using namespace std;
using namespace datastructures;

const string defaultTreeFile = "kdtree.serialized";

static void printHelp()
{
    cout << "Usage: query_kdtree tree_file query_file answers_file                      " << endl;
    cout << "                                                                           " << endl;
    cout << "    Where :                                                                " << endl;
    cout << "                                                                           " << endl;
    cout << "      sample_file        - path CSV file containing sample points data     " << endl;
    cout << "                           as prescribed by the assignment                 " << endl;
    cout << "                                                                           " << endl;
    cout << "      tree_file          - path to file where KDTree will be serialized    " << endl;
    cout << "                           Default value is '" << defaultTreeFile << "     " << endl;
    cout << "                           Note that all contents of an existing file will " << endl;
    cout << "                           be erased.                                      " << endl;
}

static bool validateInputs( int argc, char *argv[] )
{
    if ( argc < 2 )
    {
        return false;
    }

    return true;
}

// locations :
//     tree data  - "data/sample_data.csv"

int main( int argc, char *argv[] )
{
    if ( !validateInputs( argc, argv ) )
    {
        printHelp();
        return 1;
    }

    const string sampleFileName = argv[ 1 ];

    ifstream treeData( sampleFileName );

    if ( !treeData.is_open() )
    {
        cerr << "Unable to open '" << sampleFileName << "' for reading"
                  << endl;
        return 1;
    }

    Types::Points< double > points;
    string line;

    while ( getline ( treeData, line ) )
    {
        Types::Point< double > point;
        size_t pos = 0;

        while ( true )
        {
            point.push_back( static_cast< double >( stof( line, &pos ) ) );

            if ( line[ pos ] == ',')
            {
                line = line.substr( pos + 1u );
            }
            else
            {
                break;
            }
        }

        points.push_back( point );
    }
    treeData.close();

    string treeFileName;
    if ( 2 == argc )
    {
        treeFileName = defaultTreeFile;
    }
    else
    {
        treeFileName = argv[ 2 ];
    }

    KDTree< double > tree( points );
    cout << tree << endl;

    if ( !tree.serialize( treeFileName )  )
    {
        cout << "Unable to serialize KDTree" << endl;
        return 1;
    }

    cout << "Done" << endl;
    cout << "    KDTree is serialized to  : " << treeFileName << endl;

    return 0;
}