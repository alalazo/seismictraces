#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Default construction leaves the underlying buffer uninitialized
    //
    BinaryFileHeader bfh;
    
    //
    // Single fields can be assigned using enum constants in BinaryFieldHeader
    //
        
    bfh[field(bfh::rev1::jobID)]       = 20;    
    bfh[field(bfh::rev1::lineNumber)]  = 121;    
    bfh[field(bfh::rev1::reelNumber)]  = 91;    
    bfh[field(bfh::rev1::nDataTraces)] = 0;
    bfh[field(bfh::rev1::formatCode)]  = SegyFileFormatCode::IEEEfloat32;
        
    /* ... */
    
    //
    // A BinaryFileHeader may be streamed
    // 
    cout << bfh << endl;
    
    return 0;
}

