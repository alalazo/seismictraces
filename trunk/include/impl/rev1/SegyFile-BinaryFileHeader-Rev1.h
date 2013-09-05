#ifndef SEGYFILE_BINARYFILEHEADER_REV1_H
#define	SEGYFILE_BINARYFILEHEADER_REV1_H


#include<impl/rev0/SegyFile-BinaryFileHeader-Rev0.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>

namespace seismic {
    
    template<>
    class ConcreteBinaryFileHeader<Rev1> : public ConcreteBinaryFileHeader<Rev0> {
        
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();

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

