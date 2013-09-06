/// @todo TO BE REMOVED AS SOON AS A FACTORY IS READY
#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>

#include<SegyFile.h>
#include<Conversion.h>
#include<example_macro.h>

#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open a SEG Y file in read mode
    //
    TextualFileHeader tfh;
    BinaryFileHeader&  bfh = *(new ConcreteBinaryFileHeader<Rev1>);

    SegyFile segyFile( DATA_FOLDER "/mig_08gars1_6s.sgy",tfh,bfh);
    
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
    
    delete &bfh;
    return 0;
}

