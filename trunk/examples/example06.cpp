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
#include<example_macro.h>

#include<vector>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open input SEG Y file in read mode
    //
    SegyFile segyFile( DATA_FOLDER "/l10f1.sgy" , "Rev1");
    
    //cout << segyFile.getTextualFileHeader() << endl;
    cout << segyFile.getBinaryFileHeader() << endl;
        
    //
    // Read all the samples and convert the traces to a more manageable format
    //
    cout << "Number of traces : " << segyFile.ntraces() << endl;
    
    vector< SegyFile::trace_type > segyTraces;    
    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {      
        segyTraces.push_back( segyFile.readTrace(ii) );
        if( ii%1000 == 0 ) {
            cout << segyTraces[ii].first << endl;
        }
    }
    
    //
    // Modify a couple of traces
    //
    
    //size_t traceIdx = 5;
    //ViewTraceDataAs<float> trace( segyTraces[traceIdx].second );
//    
//    traceIdx = 10;
//    for( size_t ii = 0; ii < 10; ++ii) {    
//        seismicTraces[traceIdx].push_back(ii);
//    }
    
    //
    // Write to a new SEG Y file
    //
//    
//    TextualFileHeader otfh;
//    BinaryFileHeaderInterface  obfh(bfh);
//    
//    otfh[1] = "EXAMPLE06";
//    
//    obfh[BinaryFileHeader::fixedLengthTraceFlag] = 0;
    SegyFile segyOutputFile( DATA_FOLDER "/dummy.segy","Rev1" );
//    
//    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {
//        segyConverter( seismicTraces[ii], segyTraces[ii] );
//        segyOutputFile.append( segyTraces[ii] );
//    }
    segyOutputFile.getBinaryFileHeader() = segyFile.getBinaryFileHeader();
    segyOutputFile.commitFileHeaderModifications();
    //remove( DATA_FOLDER "/dummy.segy" );
    return 0;
}

