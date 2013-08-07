#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace std;

int main() {

    //
    // Default construction leaves the underlying buffer uninitialized
    //
    BinaryFileHeader bfh;
    
    //
    // Single fields can be assigned using enum constants in BinaryFieldHeader
    //
    
    bfh[BinaryFileHeader::jobID]       = 20;    
    bfh[BinaryFileHeader::lineNumber]  = 121;    
    bfh[BinaryFileHeader::reelNumber]  = 91;    
    bfh[BinaryFileHeader::nDataTraces] = 0;
    bfh[BinaryFileHeader::formatCode]  = SegyFileFormatCode::IEEEfloat32;
    /* ... */
    
    //
    // A BinaryFileHeader may be streamed
    // 
    cout << bfh << endl;
    
    return 0;
}

