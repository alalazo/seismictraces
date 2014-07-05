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
    cout << segyFile.getTextualFileHeader() << endl;
    cout << segyFile.getBinaryFileHeader() << endl;

    // 
    // Read trace number 5 from file
    //
    auto trace = segyFile.readTrace(5);
    
    //
    // Output trace header information
    //
    cout << trace.first << endl;
    
    seismic::Trace<float> strace(trace.first);
    cout << strace[rev0::th::nsamplesTrace] << endl;
    strace.push_back(0);
    cout << strace[rev0::th::nsamplesTrace] << endl;
    
    auto tt = segyFile.readTraceAs<float>(5);
    
    for( const auto& x : tt) {
        cout << x << endl;
    }
    
    //auto trace_data_view = view_as<float>( trace );
    
    //
    // Convert the trace to a more manageable format
    // 
    //SegyConverter segyConverter(segyFile.getBinaryFileHeader());
    //SeismicTrace  seismicTrace;
    
    //segyConverter(trace,seismicTrace);
    
    //
    // Print trace values 
    //
//    for(size_t ii = 0; ii < seismicTrace.size(); ii++) {
//        cout << seismicTrace[ii] << endl;
//    }
//    
    return 0;
}

