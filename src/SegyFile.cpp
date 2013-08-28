#include<SegyFile.h>

#include<impl/utilities-inl.h>

#include<algorithm>
#include<stdexcept>
#include<sstream>

using namespace std;

namespace seismic {

    ////////////////////
    // Convenience functions
    ////////////////////

    namespace {

        /**
         * @brief Functor that given a field of a binary header file, swaps its byte order
         */
        class BfhSwapByteOrder {
        public:

            BfhSwapByteOrder(BinaryFileHeader& bfh) : bfh_(bfh) {
            }

            void operator()(BinaryFileHeader::Int16Fields idx) {
                invertByteOrder(bfh_[idx]);
            }

            void operator()(BinaryFileHeader::Int32Fields idx) {
                invertByteOrder(bfh_[idx]);
            }

        private:
            BinaryFileHeader& bfh_;
        } ;

        /**
         * @brief Functor that given a field of a trace header file, swaps its byte order
         */
        class ThSwapByteOrder {
        public:

            ThSwapByteOrder(TraceHeader& th) : th_(th) {
            }

            void operator()(TraceHeader::Int16Fields idx) {
                invertByteOrder(th_[idx]);
            }

            void operator()(TraceHeader::Int32Fields idx) {
                invertByteOrder(th_[idx]);
            }

        private:
            TraceHeader& th_;
        } ;
        
    }

    
    SegyFile::SegyFile(
            const char * filename, TextualFileHeader& tfh, BinaryFileHeader& bfh,
            std::ios_base::openmode mode)
    : fstream_(filename, mode | ios_base::binary), // A SEG Y file is always opened in binary mode
    tfh_(tfh), bfh_(bfh) {
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
            fstream_.read(bfhBuffer, BinaryFileHeader::buffer_size);
#ifdef LITTLE_ENDIAN
            {
                // If the system is little endian, bytes must be swapped
                BfhSwapByteOrder swapVisitor(bfh_);
                for_each(BinaryFileHeader::Int32List.begin(), BinaryFileHeader::Int32List.end(), swapVisitor);
                for_each(BinaryFileHeader::Int16List.begin(), BinaryFileHeader::Int16List.end(), swapVisitor);
            }
#endif            
            // Check binary file header for inconsistencies
            try {
                checkBinaryFileHeader( bfh_ );
            } catch( runtime_error & e ) {
                stringstream estream;
                estream << "FATAL ERROR: " << filename << " is a non-conforming SEG Y file" << endl << endl;
                estream << "Problem encountered in binary file header:" << endl;
                estream << e.what();
                throw runtime_error( estream.str() );
            }            
            // Compute the correct size of a single data sample
            sizeOfDataSample_ = constants::sizeOfDataSample( bfh_[BinaryFileHeader::formatCode] );
            // Check the presence of extended textual file header
            nextendedTextualFileHeader_ = bfh_[BinaryFileHeader::nextendedTextualFileHeader];
            // Read Extended textual file headers
            /// TODO: to be implemented

            //////////
            // Construct the vector of strides to permit random access to traces
            //////////            
            size_t segyFileSize = fstream_.seekg(0, ios::end).tellg();
            // FIXME: change as soon as Extended textual file header is implemented
            size_t currentStride = TextualFileHeader::line_length * TextualFileHeader::nlines + BinaryFileHeader::buffer_size + nextendedTextualFileHeader_ * 3200;
            traceSeekStrides_.push_back( currentStride );

            while ( true ) {

                size_t nsamples(0);
                // Compute the number of samples in the next trace to update the stride
                if ( bfh_[BinaryFileHeader::fixedLengthTraceFlag] == 0 ) {
                    //
                    // If the traces does not have fixed length, the file 
                    // must be inspected sequentially
                    //
                    TraceHeader th;
                    // Move to the start of the next trace header and read it
                    fstream_.seekg ( currentStride );
                    readTraceHeader( th );
                    nsamples = th[TraceHeader::nsamplesTrace];
                } else if ( bfh_[BinaryFileHeader::fixedLengthTraceFlag] == 1 ) {
                    //
                    // If the traces have all fixed length the strides can be
                    // computed without inspecting the file sequentially
                    //
                    nsamples = bfh_[BinaryFileHeader::nsamplesDataTrace];
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

            /// @todo TO BE IMPLEMENTED
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
    
    ////////////////////
    // Private functions
    ////////////////////

    void SegyFile::readTraceHeader(TraceHeader& th) {
        fstream_.read( th.get(), TraceHeader::buffer_size );
#ifdef LITTLE_ENDIAN
        {
            // If the system is little endian, bytes must be swapped
            ThSwapByteOrder swapVisitor(th);
            for_each(TraceHeader::Int32List.begin(), TraceHeader::Int32List.end(), swapVisitor);
            for_each(TraceHeader::Int16List.begin(), TraceHeader::Int16List.end(), swapVisitor);
        }
#endif    
    }
    
    void SegyFile::readTraceData(const TraceHeader& th, TraceData& td) {
        // Retrieve the raw data
        const size_t nsamples = th[TraceHeader::nsamplesTrace];
        td.resize( sizeOfDataSample_*nsamples );
        fstream_.read( &td[0] , sizeOfDataSample_*nsamples );
#ifdef LITTLE_ENDIAN
        {
            // If the system is little endian, bytes must be swapped
            for( size_t ii = 0 ; ii < nsamples; ii++) {
                invertByteOrder(&td[ii*sizeOfDataSample_],sizeOfDataSample_);
            }
        }
#endif    
    }
    
    
//    void SegyFile::convertRawDataSamples(SeismicTrace& trace, std::vector<char>& buffer) {
//        switch( bfh_[BinaryFileHeader::formatCode] ) {
//            case( constants::SegyFileFormatCode::Fixed32 ):                
//                break;                
//            case( constants::SegyFileFormatCode::IEEEfloat32 ):                
//                break;
//            case( constants::SegyFileFormatCode::IBMfloat32 ):
//                break;                
//            case( constants::SegyFileFormatCode::Int32 ):                
//                break;                
//            case( constants::SegyFileFormatCode::Int16 ):
//                break;                
//            case( constants::SegyFileFormatCode::Int8  ):
//                break;                
//        }
//    }
}
