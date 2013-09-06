/**
 * @file SegyFile-BinaryFileHeader-Rev1.h
 */
#ifndef SEGYFILE_BINARYFILEHEADER_REV1_H
#define	SEGYFILE_BINARYFILEHEADER_REV1_H


#include<impl/rev0/SegyFile-BinaryFileHeader-Rev0.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>

namespace seismic {
    /**
     * @brief Models the Binary file header of a REV 1 SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The 400-byte Binary File Header record contains binary values that 
     * > affect the whole SEG Y file.  The values in the Binary File Header 
     * > are defined as two-byte or four-byte, two's complement integers.  
     * > Certain values in this header are crucial for the processing of the 
     * > data in the file, particularly the sampling interval, trace length and
     * > format code.  This revision defines a few additional fields in the 
     * > optional portion, as well as providing some clarification on the use 
     * > of some existing entries.
     * 
     * The following is a small example of the basic use of the class:
     * @include example03.cpp
     */
    template<>
    class ConcreteBinaryFileHeader<Rev1> : public ConcreteBinaryFileHeader<Rev0> {
    public:
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();
        /* virtual */
        void checkConsistencyOrThrow();
    private:
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector< rev1::bfh::Int16FieldsRev1 > Int16List;

    };
    
}

#endif	/* SEGYFILE_BINARYFILEHEADER_REV1_H */

