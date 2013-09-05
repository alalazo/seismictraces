#ifndef SEGYFILE_BINARYFILEHEADER_REV0_H
#define	SEGYFILE_BINARYFILEHEADER_REV0_H

#include<impl/SegyFile-BinaryFileHeaderInterface.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>

#include<vector>

namespace seismic {

    template<>
    class ConcreteBinaryFileHeader<Rev0> : public BinaryFileHeaderInterface {
    public:
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();
    private:
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector< rev0::bfh::Int32FieldsRev0 > Int32List;

        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int16Fields
         */
        static const std::vector< rev0::bfh::Int16FieldsRev0 > Int16List;

    };

}

#endif	/* SEGYFILE_BINARYFILEHEADER_REV0_H */

