#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-constants.h>
#include<iostream>

using namespace seismic;
using namespace std;

int main() {

    BinaryFileHeader bfh;
    
    bfh[BinaryFileHeader::jobID] = 20;
    
    bfh[BinaryFileHeader::sampleInterval] = 0;
    bfh[BinaryFileHeader::formatCode]     = SegyFileFormatCode::IEEEfloat32;
    
    cout << bfh << endl;
    
    return 0;
}

