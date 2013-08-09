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
//    cout << tfh << endl;
//    cout << bfh << endl;
    
    SegyFile segyFile("/home/mculpo/eni/wdir/seismicTraces/data/C3NAflat.segy",tfh,bfh);
    
    //
    // Output header information
    //    
    cout << tfh << endl;
    cout << bfh << endl;
    
    return 0;
}

