#include<SegyFile.h>

#include<string>
#include<stdexcept>
#include<iostream>

#include<cstdlib>

using namespace std;
using namespace seismic;

int main(int argc, char** argv) {

    try {
        if ( argc < 3 ) {
            throw runtime_error("Wrong number of parameters");
        }
        
        /// @todo CLI PARAMETERS HANDLING TO BE IMPLEMENTED        
        char * inputFilename  = argv[1];
        int    traceId        = atoi( argv[2] );
        //char * outputFilename = argv[3];
        
        // Open SEG Y file for reading 
        TextualFileHeader tfh;
        BinaryFileHeader  bfh;
        
        SegyFile segyFile(inputFilename,tfh,bfh);
        
        // Dump header information
        cout << bfh << endl;
        
        SegyFile::trace_type segyTrace = segyFile.read( traceId );
        
        cout << segyTrace.first << endl;
        
    } catch ( exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

