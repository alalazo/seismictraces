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
#include<SeismicTrace-inl.h>

using namespace seismic;

int main() {
        
    SeismicTrace trace;
    
    //
    // Set the coordinates of the receiver
    //
    trace(SeismicTrace::X) = 0.1f;
    trace(SeismicTrace::Y) = 0.2f;
    trace(SeismicTrace::Z) = 0.3f;
    
    //
    // Set the coordinates of the shot
    //
    trace.shot(SeismicTrace::X) = 10.1f;
    trace.shot(SeismicTrace::Y) = 20.1f;
    trace.shot(SeismicTrace::Z) = 30.1f;
    
    //
    // Set the time sampling interval
    //
    trace.dt() = 0.1f;
    
    //
    // Push back samples into the trace
    //
    for(int ii = 0; ii < 100; ii++) {
        trace.push_back(ii*2.5f);
    }
        
    return 0;
}
