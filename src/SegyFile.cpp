#include<SegyFile.h>

#include<algorithm>
#include<stdexcept>
#include<sstream>

#include "impl/rev0/SegyFile-Fields-Rev0.h"
#include "impl/rev1/SegyFile-Fields-Rev1.h"

using namespace std;

namespace seismic {

    SegyFile::SegyFile(
            const char * filename, TextualFileHeader& tfh, BinaryFileHeaderInterface& bfh,
            std::ios_base::openmode mode)
    : fstream_(filename, mode | ios_base::binary), // A SEG Y file is always opened in binary mode
    tfh_(tfh), bfh_(bfh) {   
        fstream_.peek();
        if ( fstream_.good() ) {
            ////////////////////
            // If eofbit, failbit and badbit are set to false, then 
            // tfh and bfh must be read from an existing file
            ////////////////////

            // Move to the beginning of the file
            fstream_.seekg(0,ios::beg);
            // File header buffers
            char * tfhBuffer( tfh_.get() );
            char * bfhBuffer( bfh_.get() );
            // Read Textual file header (3200 bytes)
            fstream_.read(tfhBuffer, TextualFileHeader::line_length * TextualFileHeader::nlines);
            // Read Binary file header  (400 bytes)
            fstream_.read(bfhBuffer, BinaryFileHeaderInterface::buffer_size);
#ifdef LITTLE_ENDIAN
            // If the system is little endian, bytes must be swapped            
            bfh_.invertByteOrder();
#endif            
            // Check binary file header for inconsistencies
            // @todo CHECK FOR INCONSISTENCIES ON READ
//            try {
//                checkBinaryFileHeader( bfh_ );
//            } catch( runtime_error & e ) {
//                stringstream estream;
//                estream << "FATAL ERROR: " << filename << " is a non-conforming SEG Y file" << endl << endl;
//                estream << "Problem encountered in binary file header:" << endl;
//                estream << e.what();
//                throw runtime_error( estream.str() );
//            }            
            // Compute the correct size of a single data sample
            sizeOfDataSample_ = constants::sizeOfDataSample( bfh_[ field(rev1::bfh::formatCode) ] );
            // Check the presence of extended textual file header
            nextendedTextualFileHeader_ = bfh_[ field(rev1::bfh::nextendedTextualFileHeader) ];
            // Read Extended textual file headers
            /// @todo Extended textual file header section to be implemented

            //////////
            // Construct the vector of strides to permit random access to traces
            //////////            
            size_t segyFileSize = fstream_.seekg(0, ios::end).tellg();
            // FIXME: change as soon as Extended textual file header is implemented
            size_t currentStride = 
                    TextualFileHeader::line_length * TextualFileHeader::nlines +
                    BinaryFileHeaderInterface::buffer_size + 
                    nextendedTextualFileHeader_ * 3200;
            traceSeekStrides_.push_back( currentStride );

            while ( true ) {

                size_t nsamples(0);
                // Compute the number of samples in the next trace to update the stride
                if ( bfh_[ field(rev1::bfh::fixedLengthTraceFlag) ] == 0 ) {
                    //
                    // If the traces does not have fixed length, the file 
                    // must be inspected sequentially
                    //
                    TraceHeader th;
                    // Move to the start of the next trace header and read it
                    fstream_.seekg ( currentStride );
                    readTraceHeader( th );
                    nsamples = th[TraceHeader::nsamplesTrace];
                } else if ( bfh_[ field(rev1::bfh::fixedLengthTraceFlag) ] == 1 ) {
                    //
                    // If the traces have all fixed length the strides can be
                    // computed without inspecting the file sequentially
                    //
                    nsamples = bfh_[ field(rev1::bfh::nsamplesDataTrace) ];
                }
                // Update the current stride in the file
                currentStride += TraceHeader::buffer_size + sizeOfDataSample_ * nsamples;
                // Check for end of file
                if ( segyFileSize == currentStride) {
                    // If the end of the file has been reached, then stop reading
                    break;
                } else if ( segyFileSize < currentStride) {
                    // If the end of the file has been exceeded, the file is truncated
                    stringstream estream;
                    estream << "FATAL ERROR: " << filename << " is truncated after trace number " << traceSeekStrides_.size() << endl << endl;
                    estream << "The total size of the file is " << segyFileSize << " while it should be " << currentStride;
                    estream << " to contain " << (traceSeekStrides_.size() + 1) << "traces" << endl;
                    throw runtime_error( estream.str() );
                }
                // Push back value into the vector used as buffer 
                traceSeekStrides_.push_back( currentStride );
            }

        } else {
            ////////////////////
            // If file was opened for writing tfh and bfh 
            // must be written to a newly created file
            ////////////////////
            fstream_.clear();
            // Set number of traces to zero, as the file starts empty
            fstream_.seekp(0,ios_base::beg);
            // File header buffers
            char * tfhBuffer( tfh_.get() );
            // Write Textual file header (3200 bytes)
            fstream_.write(tfhBuffer, TextualFileHeader::line_length * TextualFileHeader::nlines);

            // Write Binary file header  (400 bytes)            
            BinaryFileHeaderInterface& obfh(bfh);
            char * bfhBuffer( obfh.get() );
#ifdef LITTLE_ENDIAN
            // If the system is little endian, bytes must be swapped
            obfh.invertByteOrder();
#endif
            fstream_.write(bfhBuffer, BinaryFileHeaderInterface::buffer_size);            
            // Compute the correct size of a single data sample
            sizeOfDataSample_ = constants::sizeOfDataSample( bfh_[ field(rev1::bfh::formatCode) ] );
            // Check the presence of extended textual file header
            nextendedTextualFileHeader_ = bfh_[ field(rev1::bfh::nextendedTextualFileHeader) ];            
        }
    }
    
    SegyFile::trace_type SegyFile::read(size_t n)  {    
        SegyFile::trace_type value;
        // Check for out of ranges
        if ( n >=  traceSeekStrides_.size() ) {
            stringstream estream;
            estream << "ERROR: out-of-range trace access" << endl << endl; 
            estream << "Trying to access trace number " << n << " in a file with only " << traceSeekStrides_.size();
            estream << " traces" << endl;
            throw runtime_error( estream.str() );
        }        
        // Move to the correct position in the file        
        fstream_.seekg( traceSeekStrides_[n] );
        // Read trace header
        readTraceHeader( value.first );
        // Read trace data
        readTraceData( value.first, value.second );        
        // Return the trace
        return value;
    }
    
    void SegyFile::append(const trace_type& trace) {
        // Move to the correct position in the file        
        fstream_.seekp(0,ios_base::end);
        // Write trace header
        writeTraceHeader( trace.first  );
        // Write trace data
        writeTraceData  ( trace.second );        
    }
    
    ////////////////////
    // Private functions
    ////////////////////

    void SegyFile::readTraceHeader(TraceHeader& th) {
        fstream_.read( th.get(), TraceHeader::buffer_size );
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped
        invertFieldsByteOrder(th);
#endif    
    }

    void SegyFile::readTraceData(const TraceHeader& th, TraceData& td) {
        // Retrieve the raw data
        const size_t nsamples = th[TraceHeader::nsamplesTrace];
        td.resize( sizeOfDataSample_ * nsamples );
        fstream_.read( &td[0] , sizeOfDataSample_ * nsamples );
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped
        for ( size_t ii = 0 ; ii < nsamples; ii++) {
            invertByteOrder(&td[ii * sizeOfDataSample_], sizeOfDataSample_);
        }
#endif    
    }
    
    void SegyFile::writeTraceHeader(TraceHeader th) {        
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped
        invertFieldsByteOrder(th);
#endif    
        fstream_.write( th.get(), TraceHeader::buffer_size );
    }

    void SegyFile::writeTraceData(TraceData td) {
        const size_t nsamples = td.size() / sizeOfDataSample_;
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped
        for ( size_t ii = 0 ; ii < nsamples; ii++) {
            invertByteOrder(&td[ii * sizeOfDataSample_], sizeOfDataSample_);
        }
#endif    
        fstream_.write( &td[0] , sizeOfDataSample_ * nsamples );
    }
}
