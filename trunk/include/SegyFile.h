#ifndef SEGYFILE_H
#define	SEGYFILE_H

#include<impl/SegyFile-TextualFileHeader.h>

#include<string>
#include<iostream>

namespace seismic {
    
    class TextualFileHeader;
    class BinaryFileHeader;
    class SeismicTrace;
    
    class SegyFile {
    public:
        enum FileMode {READ, WRITE, READWRITE};
        
        SegyFile(
                const std::string& filename, const FileMode mode,
                TextualFileHeader& tfh, BinaryFileHeader& bfh
                );
        
        void read  (SeismicTrace& trace, int n) const;
        void append(SeismicTrace& trace);
        
        ~SegyFile();
        
    private:
        int ntraces_;
    };
        
}


#endif	/* SEGYFILE_H */

