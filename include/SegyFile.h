/**
 * @file SegyFile.h
 * @brief File containing data in SEG Y rev. 1 format
 */
#ifndef SEGYFILE_H
#define	SEGYFILE_H

#include<SeismicTrace-inl.h>
#include<impl/SegyFile-TextualFileHeader.h>
#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-TraceHeader.h>
#include<impl/SegyFile-constants.h>

#include<string>
#include<fstream>
#include<iostream>
#include<ios>

namespace seismic {
    
    class SegyFile {
    public:
        
        SegyFile(
                const char * filename, TextualFileHeader& tfh, BinaryFileHeader& bfh,
                std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out
                );
        
        
        void read  (SeismicTrace& trace, int n) const;
        void append(SeismicTrace& trace);
        
    private:        
        std::fstream       fstream_;        
        
        TextualFileHeader& tfh_;
        BinaryFileHeader&  bfh_;
    };
        
}


#endif	/* SEGYFILE_H */

