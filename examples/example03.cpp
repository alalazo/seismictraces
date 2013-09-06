#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Default construction leaves the underlying buffer uninitialized
    //
    BinaryFileHeader& bfh = *(new ConcreteBinaryFileHeader<Rev1>);
    
    //
    // Single fields can be assigned using enum constants in BinaryFieldHeader
    //
        
    bfh[field(rev0::bfh::jobID)]       = 20;    
    bfh[field(rev0::bfh::lineNumber)]  = 121;    
    bfh[field(rev0::bfh::reelNumber)]  = 91;    
    bfh[field(rev0::bfh::nDataTraces)] = 0;
    bfh[field(rev0::bfh::formatCode)]  = SegyFileFormatCode::IEEEfloat32;
        
    /* ... */
    
    //
    // A BinaryFileHeader may be streamed
    // 
    cout << bfh << endl;
    
    delete &bfh;
    
    return 0;
}

