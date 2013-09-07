#ifndef SEGYFILE_TRACEHEADER_REV1_H
#define	SEGYFILE_TRACEHEADER_REV1_H

#include<impl/rev0/SegyFile-TraceHeader-Rev0.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>

namespace seismic {
    
    template<>
    class ConcreteTraceHeader<Rev1> : public ConcreteTraceHeader<Rev0> {
    public:
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();
        /* virtual */
        void checkConsistencyOrThrow() const;
        /* virtual */
        ConcreteTraceHeader<Rev1> * create() const {
            return new ConcreteTraceHeader<Rev1>;
        }
        
    private:
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector< rev1::th::Int32FieldsRev1 > Int32List;

        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int16Fields
         */
        static const std::vector< rev1::th::Int16FieldsRev1 > Int16List;

        /**
         * @brief Field needed to register the class into its factory
         */
        static const bool isRegistered;
    };
    
}

#endif	/* SEGYFILE_TRACEHEADER_REV1_H */

