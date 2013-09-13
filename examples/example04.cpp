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
    
    th[ field(rev1::th::traceSequenceNumberWithinLine) ] = 20;    
    th[ field(rev1::th::traceSequenceNumberWithinSEGY) ] = 121;    
    th[ field(rev1::th::sourceCoordinateX) ]             = 91;    
    th[ field(rev1::th::sourceCoordinateY) ]             = 0;
    th[ field(rev1::th::nsamplesTrace) ]                 = 101;
    /* ... */
    
    //
    // A TraceHeader may be streamed
    // 
    cout << th << endl;
    
    return 0;
}

