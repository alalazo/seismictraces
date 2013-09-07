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
    BinaryFileHeader& bfh = *BinaryFileHeader::create("Rev1");
    
    //
    // Single fields can be assigned using enum constants in BinaryFieldHeader
    //
        
    bfh[field(rev1::bfh::jobID)]       = 20;    
    bfh[field(rev1::bfh::lineNumber)]  = 121;    
    bfh[field(rev1::bfh::reelNumber)]  = 91;    
    bfh[field(rev1::bfh::nDataTraces)] = 0;
    bfh[field(rev1::bfh::formatCode)]  = SegyFileFormatCode::IEEEfloat32;
        
    /* ... */
    
    //
    // A BinaryFileHeader may be streamed
    // 
    cout << bfh << endl;
    
    delete &bfh;
    
    return 0;
}

