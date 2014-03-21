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
#include<impl/SegyFile-TextualFileHeader.h>

#include<iostream>

using namespace seismic;
using namespace std;

int main() {

    //
    // When a TextualFileHeader is constructed, its buffer table is initialized
    // to avoid the presence of garbage entries
    //
    TextualFileHeader tfh;
        
    // A single line in the text header file can be assigned from:
    
    //
    // 1. Raw literals
    // 
    tfh[0] = "This is a fake first line!";
    
    //
    // 2. C++ strings
    //
    string line("The best second line ever! :-)");
    tfh[1] = line;
    
    //
    // 3. Other Lines
    //
    tfh[2] = tfh[1];
    
    // Exceptions are thrown for out of range accesses
    
    try {
      tfh[40] = "Assign out of range";
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
    try {
      tfh[0][80] = '@';
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
    
    //
    // A TextualFileHeader may be streamed 
    // 
    cout << tfh << endl;        
    
    return 0;
}

