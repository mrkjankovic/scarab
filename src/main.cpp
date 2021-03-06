/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <rapidjson/document.h>

#include "Scarab/simulator.hpp"

int main( const int numberOfInputs, const char* inputArguments[ ] )
{
    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                              Scarab                              " << std::endl;
    std::cout << "         Simulator for close-range removal of Ariane bodies       " << std::endl;

    std::cout << "                              0.0.1                               " << std::endl;
    std::cout << std::endl;
    std::cout << "                      Copyright (c) 2014-2015                     " << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                          Input parameters                        " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Check that only one input has been provided (a JSON file).
    if ( numberOfInputs - 1 != 1 )
    {
        std::cerr << "ERROR: Number of inputs is wrong. Please only provide a JSON input file!"
                  << std::endl;
        throw;
    }

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    // Read and store JSON input document (filter out comment lines).
    // TODO: Need to make comment-line filtering more robust.
    std::ifstream inputFile( inputArguments[ 1 ] );
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;
    while ( std::getline( inputFile, inputLine ) )
    {
        size_t startPosition = inputLine.find_first_not_of( " \t" );
        if ( std::string::npos != startPosition )
        {
            inputLine = inputLine.substr( startPosition );
        }

        if ( inputLine.substr( 0, 2 ) != "//" )
        {
            jsonDocumentBuffer << inputLine << "\n";
        }
    }

    rapidjson::Document config;
    config.Parse( jsonDocumentBuffer.str( ).c_str( ) );

    // Execute simulator.
    scarab::executeSimulator( config );

    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                        Exited successfully!                      " << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;

    ///////////////////////////////////////////////////////////////////////////
}
