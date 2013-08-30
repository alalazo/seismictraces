#include<SegyFile.h>
#include<Conversion.h>
#include<example_macro.h>

#include<vector>
#include<iostream>

using namespace seismic;
using namespace seismic::constants;
using namespace std;

int main() {

    //
    // Open input SEG Y file in read mode
    //
    TextualFileHeader tfh;
    BinaryFileHeader  bfh;
    
    SegyFile segyFile( DATA_FOLDER "/C3NAflat.segy",tfh,bfh);
    
    //
    // Read all the samples and convert the traces to a more manageable format
    //
    
    vector< SegyFile::trace_type > segyTraces;
    vector< SeismicTrace >         seismicTraces( segyFile.ntraces() );
    SegyConverter                  segyConverter(bfh);
    
    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {      
        segyTraces.push_back( segyFile.read(ii) );
        segyConverter( segyTraces[ii],seismicTraces[ii] );
    }
    
    //
    // Modify a couple of traces
    //
    
    size_t traceIdx = 5;
    seismicTraces[traceIdx].resize( 10, 3.0f );
    
    traceIdx = 10;
    for( size_t ii = 0; ii < 10; ++ii) {    
        seismicTraces[traceIdx].push_back(ii);
    }
    
    //
    // Write to a new SEG Y file
    //
    
    TextualFileHeader otfh;
    BinaryFileHeader  obfh(bfh);
    
    otfh[1] = "EXAMPLE06";
    
    obfh[BinaryFileHeader::fixedLengthTraceFlag] = 0;
    SegyFile segyOutputFile( DATA_FOLDER "/C3NAflat.copy.segy",otfh,obfh, ios_base::out );
    
    for(size_t ii = 0; ii < segyFile.ntraces(); ++ii) {
        segyConverter( seismicTraces[ii], segyTraces[ii] );
        segyOutputFile.append( segyTraces[ii] );
    }
    
    return 0;
}

