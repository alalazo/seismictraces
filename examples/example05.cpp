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
#include<impl/SegyFile-Trace.h>
#include<example_macro.h>

#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open a SEG Y file in read mode
    //
    SegyFile segyFile( DATA_FOLDER "/mig_08gars1_6s.sgy", "Rev0");
    
    //
    // Output header information
    //    
    ebcdic2ascii(segyFile.getTextualFileHeader());
    cout << segyFile.getTextualFileHeader() << endl;
    cout << segyFile.getBinaryFileHeader() << endl;

    // 
    // Read trace number 5 from file
    //
    auto raw_trace = segyFile.readRawTrace(5);
    
    //
    // Output trace header information
    //
    cout << raw_trace.first << endl;
    
    //
    // Read the trace converting it to a more manageable format
    //            
    auto trace = segyFile.readTraceAs<float>(5);
    
    //
    // Output trace header information as before
    //    
    cout << trace << endl;    
    
    //
    // Data now is in floating point format, and can be handled like an std::vector
    //

    for( const auto & x : trace ) {
        cout << x << endl;
    }
    return 0;
}

