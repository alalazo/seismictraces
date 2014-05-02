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
/// @todo TO BE REMOVED AS SOON AS A FACTORY IS READY
#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>

#include<SegyFile.h>
#include<Conversion.h>
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
    TextualFileHeader tfh;
    
    BinaryFileHeader&  bfh = *(new ConcreteBinaryFileHeader<Rev1>);

    SegyFile segyFile( DATA_FOLDER "/mig_08gars1_6s.sgy",tfh,bfh);
    
    cout << bfh << endl;
    
    //
    // Read all the samples and convert the traces to a more manageable format
    //
    
    vector< SegyFile::trace_type > segyTraces;
    vector< SeismicTrace >         seismicTraces( segyFile.ntraces() );
    SegyConverter                  segyConverter(bfh);
    
    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {      
        segyTraces.push_back( segyFile.read(ii) );
        segyConverter( segyTraces[ii],seismicTraces[ii] );
    }
    
    //
    // Modify a couple of traces
    //
    
    size_t traceIdx = 5;
    seismicTraces[traceIdx].resize( 10, 3.0f );
    
    traceIdx = 10;
    for( size_t ii = 0; ii < 10; ++ii) {    
        seismicTraces[traceIdx].push_back(ii);
    }
    
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
//    SegyFile segyOutputFile( DATA_FOLDER "/C3NAflat.copy.segy",otfh,obfh, ios_base::out );
//    
//    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {
//        segyConverter( seismicTraces[ii], segyTraces[ii] );
//        segyOutputFile.append( segyTraces[ii] );
//    }
//
    delete &bfh;    
    return 0;
}

