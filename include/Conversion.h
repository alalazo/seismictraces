/**
 * @file  ConversionManager.h
 * @brief Conversion functions between objects of different format
 */
#ifndef CONVERSION_H
#define	CONVERSION_H

#include<SegyFile.h>
#include<SeismicTrace-inl.h>

namespace seismic {
    
    /**
     * @brief Manages conversion between SegyFile::trace_type and SeismicTrace objects
     * 
     * The following is a small example of the basic use of the class:
     * @include example05.cpp     
     */
    class SegyConverter {
    public:
        /**
         * @brief Unique and only constructor
         * 
         * @param[in] bfh binary file header
         */
        explicit SegyConverter(const BinaryFileHeaderInterface& bfh) : bfh_(bfh) {}
        
        /**
         * @brief Convert a SegyFile::trace_type object to a SeismicTrace object
         * 
         * @param[in]  segyTrace input trace in SEGY format
         * @param[out] seismicTrace converted output
         */
        void operator()(const SegyFile::trace_type& segyTrace, SeismicTrace& seismicTrace);

        /**
         * @brief Convert a SeismicTrace object to a SegyFile::trace_type object
         * 
         * @param[in] seismicTrace
         * @param[in,out] segyTrace
         */
        void operator()(const SeismicTrace& seismicTrace, SegyFile::trace_type& segyTrace);
        
    private:
        const BinaryFileHeaderInterface& bfh_;
    } ;
    
}

#endif	/* CONVERSION_H */

