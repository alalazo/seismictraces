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

#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open a SEG Y file in read mode
    //
    TextualFileHeader tfh;
    BinaryFileHeader&  bfh = *(new ConcreteBinaryFileHeader<Rev1>);

    SegyFile segyFile( DATA_FOLDER "/mig_08gars1_6s.sgy",tfh,bfh);
    
    //
    // Output header information
    //    
    cout << tfh << endl;
    cout << bfh << endl;

    // 
    // Read trace number 5 from file
    //
    SegyFile::trace_type trace = segyFile.read(5);
    
    //
    // Output trace header information
    //
    cout << trace.first << endl;
        
    //
    // Convert the trace to a more manageable format
    // 
    SegyConverter segyConverter(bfh);
    SeismicTrace  seismicTrace;
    
    segyConverter(trace,seismicTrace);
    
    //
    // Print trace values 
    //
    for(size_t ii = 0; ii < seismicTrace.size(); ii++) {
        cout << seismicTrace[ii] << endl;
    }
    
    delete &bfh;
    return 0;
}

