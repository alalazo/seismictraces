/**
 * @file SegyFile-TraceHeaderInterface.h
 * @brief Generic interface to a trace header
 */
#ifndef SEGYFILE_TRACEHEADERINTERFACE_H
#define	SEGYFILE_TRACEHEADERINTERFACE_H

#include<impl/GenericByteStream-inl.h>

#include<vector>
#include<iostream>

namespace seismic {
    
    typedef GenericByteStream<240> TraceHeaderInterface;
            
    /**
     * @brief Master template to be specialized for different standards
     */
    template<class StdTag>
    class ConcreteTraceHeader;
        
}

#endif	/* SEGYFILE_TRACEHEADERINTERFACE_H */

