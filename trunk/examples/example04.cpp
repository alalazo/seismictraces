#include<impl/SegyFile-TraceHeader.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Default construction leaves the underlying buffer uninitialized
    //
    TraceHeader th;
    
    //
    // Single fields can be assigned using enum constants in TraceHeader
    //
    
    th[TraceHeader::traceSequenceNumberWithinLine] = 20;    
    th[TraceHeader::traceSequenceNumberWithinSEGY] = 121;    
    th[TraceHeader::sourceCoordinateX]             = 91;    
    th[TraceHeader::sourceCoordinateY]             = 0;
    th[TraceHeader::nsamplesTrace]                 = 101;
    /* ... */
    
    //
    // A TraceHeader may be streamed
    // 
    cout << th << endl;
    
    return 0;
}

