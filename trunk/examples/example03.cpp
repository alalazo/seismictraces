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
#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-constants.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {
    
    //
    // Default construction leaves the underlying byte stream initialized to 0
    //
    BinaryFileHeader::smart_reference_type bfh( BinaryFileHeader::create("Rev1") );
    
    //
    // Single fields can be assigned using enum constants in BinaryFieldHeader
    //
        
    bfh[rev1::bfh::jobID]       = 20;    
    bfh[rev1::bfh::lineNumber]  = 121;    
    bfh[rev1::bfh::reelNumber]  = 91;    
    bfh[rev1::bfh::nDataTraces] = 0;
    bfh[rev1::bfh::formatCode]  = SegyFileFormatCode::IEEEfloat32;
        
    /* ... */
    
    //
    // A BinaryFileHeader may be streamed
    // 
    cout << bfh << endl;
    
    return 0;
}

