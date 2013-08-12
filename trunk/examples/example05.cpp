#include<SegyFile.h>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open a SEG Y file in read mode
    //
    TextualFileHeader tfh;
    BinaryFileHeader  bfh;
    
    SegyFile segyFile("/home/mculpo/eni/wdir/seismicTraces/data/C3NAflat.segy",tfh,bfh);
    
    //
    // Output header information
    //    
    cout << tfh << endl;
    cout << bfh << endl;

    // 
    // Read trace number 5 from file
    //
    SegyFile::trace_type trace = segyFile.read(5);
    
    //
    // Output trace header information
    //
    cout << trace.first << endl;
        
    return 0;
}

