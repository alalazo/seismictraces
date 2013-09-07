#ifndef SEGYFILE_TRACEHEADER_REV0_H
#define	SEGYFILE_TRACEHEADER_REV0_H

#include<impl/SegyFile-TraceHeaderInterface.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>

namespace seismic {
    
    template<>
    class ConcreteTraceHeader<Rev0> : public TraceHeaderInterface {
    public:
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();
        /* virtual */
        void checkConsistencyOrThrow() const;
        /* virtual */
        ConcreteTraceHeader<Rev0> * create() const {
            return new ConcreteTraceHeader<Rev0>;
        }
        
    private:
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector< rev0::th::Int32FieldsRev0 > Int32List;

        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int16Fields
         */
        static const std::vector< rev0::th::Int16FieldsRev0 > Int16List;

        /**
         * @brief Field needed to register the class into its factory
         */
        static const bool isRegistered;
    };
    
}

#endif	/* SEGYFILE_TRACEHEADER_REV0_H */

