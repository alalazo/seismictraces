/**
 * @file SegyFile-BinaryFileHeader.h
 * @brief Generic interface to a binary file header
 */
#ifndef SEGYFILE_BINARYFILEHEADER_H
#define	SEGYFILE_BINARYFILEHEADER_H

#include<impl/GenericByteStream-inl.h>

#include<vector>
#include<iostream>
#include<string>
#include<memory>

namespace seismic {
    
    typedef GenericByteStream<400> BinaryFileHeader;
    
    /**
     * @brief Master template to be specialized for different standards
     */
    template< class StdTag>
    class ConcreteBinaryFileHeader;
         
}

#endif	/* SEGYFILE_BINARYFILEHEADER_H */

