#include<SegyFile.h>
#include<Conversion.h>

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
    
    /// @fixme: Add a relative path here
    SegyFile segyFile("/home/mculpo/eni/seismicTraces/data/C3NAflat.segy",tfh,bfh);
    
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
        
    //
    // Convert the trace to a more manageable format
    // 
    SegyConverter segyConverter(bfh);
    SeismicTrace  seismicTrace;
    
    segyConverter(trace,seismicTrace);
    
    //
    // Print trace values 
    //
    for(size_t ii = 0; ii < seismicTrace.size(); ii++) {
        cout << seismicTrace[ii] << endl;
    }
    
    return 0;
}

