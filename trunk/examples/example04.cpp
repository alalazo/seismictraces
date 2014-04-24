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
#include<impl/SegyFile-TraceHeaderInterface.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Default construction leaves the underlying buffer uninitialized
    //
    TraceHeaderInterface::smart_reference_type th( TraceHeaderInterface::create("Rev1") );
    
    //
    // Single fields can be assigned using enum constants in TraceHeader
    //
    
    th[ rev1::th::traceSequenceNumberWithinLine ] = 20;
    th[ rev1::th::traceSequenceNumberWithinSEGY ] = 121;    
    th[ rev1::th::sourceCoordinateX ]             = 91;    
    th[ rev1::th::sourceCoordinateY ]             = 0;
    th[ rev1::th::nsamplesTrace ]                 = 101;
    /* ... */
    
    //
    // A TraceHeader may be streamed
    // 
    cout << th << endl;
    
    return 0;
}

