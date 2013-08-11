#include<SegyFile.h>

#include<impl/utilities-inl.h>

#include<algorithm>
#include<stdexcept>
#include<sstream>

using namespace std;

namespace {

    /**
     * @brief Functor that given a field of a binary header file, swaps its byte order
     */
    class BfhSwapByteOrder {
    public:

        BfhSwapByteOrder(seismic::BinaryFileHeader& bfh) : bfh_(bfh) {
        }

        void operator()(seismic::BinaryFileHeader::Int16Fields idx) {
            seismic::swapByteOrder(bfh_[idx]);
        }

        void operator()(seismic::BinaryFileHeader::Int32Fields idx) {
            seismic::swapByteOrder(bfh_[idx]);
        }

    private:
        seismic::BinaryFileHeader& bfh_;
    };

    /**
     * @brief Functor that given a field of a trace header file, swaps its byte order
     */
    class ThSwapByteOrder {
    public:

        ThSwapByteOrder(seismic::TraceHeader& th) : th_(th) {
        }

        void operator()(seismic::TraceHeader::Int16Fields idx) {
            seismic::swapByteOrder(th_[idx]);
        }

        void operator()(seismic::TraceHeader::Int32Fields idx) {
            seismic::swapByteOrder(th_[idx]);
        }

    private:
        seismic::TraceHeader& th_;
    };
}

namespace seismic {

    SegyFile::SegyFile(
            const char * filename, TextualFileHeader& tfh, BinaryFileHeader& bfh,
            std::ios_base::openmode mode)
    : fstream_(filename, mode | ios_base::binary), // A SEG Y file is always opened in binary mode
    tfh_(tfh), bfh_(bfh) {
        if ((mode & ios_base::in) == ios_base::in) {
            ////////////////////
            // If file was opened for reading or reading/writing, tfh and bfh 
            // must be read from an existing file
            ////////////////////

            // File header buffers
            char * tfhBuffer(tfh_.get());
            char * bfhBuffer(bfh_.get());
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
            // Compute the correct size of a single data sample
            switch ( bfh_[BinaryFileHeader::formatCode] ) {
                case ( constants::SegyFileFormatCode::IBMfloat32 ):
                case ( constants::SegyFileFormatCode::Int32      ):
                case ( constants::SegyFileFormatCode::Fixed32    ):
                case ( constants::SegyFileFormatCode::IEEEfloat32):
                    sizeOfDataSample_ = 4;
                    break;
                case ( constants::SegyFileFormatCode::Int16      ):
                    sizeOfDataSample_ = 2;
                    break;
                case ( constants::SegyFileFormatCode::Int8       ):
                    sizeOfDataSample_ = 1;
                    break;
                default:
                    throw runtime_error("FATAL ERROR: invalid \"Data sample format code\"\n");
                    break;
            }

            //////////
            // Check the presence of extended textual file header
            //////////
            nextendedTextualFileHeader_ = bfh_[BinaryFileHeader::nextendedTextualFileHeader];
            if ( nextendedTextualFileHeader_ < -1 ) {
                stringstream estream;
                estream << "FATAL ERROR: " << filename << " is a non-conforming SEG Y file" << endl << endl;
                estream << "In binary file header the number of extended textual file header is < -1" << endl;
                throw runtime_error( estream.str() );
            }
            // Read Extended textual file headers
            /// TODO: to be implemented

            //////////
            // Construct the vector of strides to permit random access to traces
            //////////

            size_t segyFileSize = fstream_.seekg(0, ios::end).tellg();
            // FIXME: change as soon as Extended textual file header is implemented
            size_t currentStride = TextualFileHeader::line_length * TextualFileHeader::nlines + BinaryFileHeader::buffer_size + nextendedTextualFileHeader_ * 3200;
            traceSeekStrides_.push_back( currentStride );
            if ( bfh_[BinaryFileHeader::fixedLengthTraceFlag] == 1 ) {
                //
                // If the traces have all fixed length the strides can be
                // computed without inspecting the file sequentially
                //

                while ( true ) {
                    currentStride += TraceHeader::buffer_size + sizeOfDataSample_ * bfh_[BinaryFileHeader::nsamplesDataTrace];
                    if ( segyFileSize == currentStride) {
                        break;
                    } else if ( segyFileSize < currentStride) {
                        stringstream estream;
                        estream << "FATAL ERROR: " << filename << " is truncated after trace number " << traceSeekStrides_.size() << endl << endl;
                        estream << "The total size of the file is " << segyFileSize << " while it should be " << currentStride;
                        estream << " to contain " << (traceSeekStrides_.size() + 1) << "traces" << endl;
                        throw runtime_error( estream.str() );
                    }

                    traceSeekStrides_.push_back( currentStride );

                }
            } else if ( bfh_[BinaryFileHeader::fixedLengthTraceFlag] == 0 ) {
                //
                // If the traces does not have fixed length, the file must be 
                // inspected sequentially at least once
                //
                TraceHeader th;

                while ( true ) {
                    // Move to the start of the next trace header and read it
                    fstream_.seekg( currentStride ).read( th.get(), TraceHeader::buffer_size );
#ifdef LITTLE_ENDIAN
                    {
                        // If the system is little endian, bytes must be swapped
                        ThSwapByteOrder swapVisitor(th);
                        for_each(TraceHeader::Int32List.begin(), TraceHeader::Int32List.end(), swapVisitor);
                        for_each(TraceHeader::Int16List.begin(), TraceHeader::Int16List.end(), swapVisitor);
                    }
#endif    
                    currentStride += TraceHeader::buffer_size + sizeOfDataSample_ * th[TraceHeader::nsamplesTrace];
                    if ( segyFileSize == currentStride) {
                        break;
                    } else if ( segyFileSize < currentStride) {
                        stringstream estream;
                        estream << "FATAL ERROR: " << filename << " is truncated after trace number " << traceSeekStrides_.size() << endl << endl;
                        estream << "The total size of the file is " << segyFileSize << " while it should be " << currentStride;
                        estream << " to contain " << (traceSeekStrides_.size() + 1) << "traces" << endl;
                        throw runtime_error( estream.str() );
                    }

                    traceSeekStrides_.push_back( currentStride );
                }

            } else {
                stringstream estream;
                estream << "FATAL ERROR: " << filename << " is a non-conforming SEG Y file" << endl << endl;
                estream << "In binary file header the 'fixed length trace flag' (bytes 3503-3504)";
                estream << " has the invalid value of " << bfh_[BinaryFileHeader::fixedLengthTraceFlag];
                estream << " (valid values are 0/1) " << endl;
                throw runtime_error( estream.str() );
            }
            
        } else {
            ////////////////////
            // If file was opened for writing tfh and bfh 
            // must be written to a newly created file
            ////////////////////

            // TO BE IMPLEMENTED
        }
    }

}
