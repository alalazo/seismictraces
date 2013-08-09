#include<SegyFile.h>

#include<impl/utilities-inl.h>

#include<algorithm>

using namespace std;

namespace {
    
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
            // If the system is little endian, bytes must be swapped
            BfhSwapByteOrder swapVisitor(bfh_);
            for_each( BinaryFileHeader::Int32List.begin(),BinaryFileHeader::Int32List.end(),swapVisitor );            
            for_each( BinaryFileHeader::Int16List.begin(),BinaryFileHeader::Int16List.end(),swapVisitor );            
//          for (int ii = 0; ii < 400; ii++) {
//              cout << std::dec << std::noshowbase << ii << ' ';
//              cout << std::hex << std::showbase << (short) bfhBuffer[ii] << endl;
//          }
            
#endif
        } else {
            ////////////////////
            // If file was opened for writing tfh and bfh 
            // must be written to a newly created file
            ////////////////////
            
            // TO BE IMPLEMENTED
        }
    }
    
}
