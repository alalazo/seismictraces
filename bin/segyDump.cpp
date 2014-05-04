/*
 *  SeismicTraces : another C++ library that reads files in SEG-Y format
 * 
 *  Copyright (C) 2014  Massimiliano Culpo
 * 
 *  This file is part of SeismicTraces.
 *
 *  SeismicTraces is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SeismicTraces is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SeismicTraces.  If not, see <http://www.gnu.org/licenses/>.
 */
#include<SegyFile.h>

/// @todo TO BE REMOVED AS SOON AS A FACTORY IS READY
#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>

#include<string>
#include<stdexcept>
#include<iostream>

#include<cstdlib>

using namespace std;
using namespace seismic;

int main(int argc, char** argv) {

    try {
        if ( argc < 3 ) {
            throw runtime_error("Wrong number of parameters");
        }
//        
//        /// @todo CLI PARAMETERS HANDLING TO BE IMPLEMENTED        
//        char * inputFilename  = argv[1];
//        int    traceId        = atoi( argv[2] );
//        //char * outputFilename = argv[3];
//        
//        // Open SEG Y file for reading 
//        SegyFile segyFile(inputFilename,"Rev1");
//        
//        // Dump header information
//        cout << segyFile.getBinaryFileHeader() << endl;
//        
//        //SegyFile::trace_type segyTrace = segyFile.read( traceId );
//        
//        cout << segyTrace.first << endl;

    } catch ( exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

